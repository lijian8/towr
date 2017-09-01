/**
 @file    force_constraint.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Aug 23, 2017
 @brief   Brief description
 */

#include <xpp/constraints/force_constraint.h>

#include <array>
#include <memory>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <xpp/cartesian_declarations.h>
#include <xpp/state.h>
#include <xpp/variables/node_values.h>

namespace xpp {
namespace opt {


ForceConstraint::ForceConstraint (const HeightMap::Ptr& terrain,
                                  double force_limit,
                                  const OptVarsPtr& opt_vars,
                                  const std::string& ee_force_id,
                                  const std::string& ee_motion_id)
{
  ee_force_  = opt_vars->GetComponent<EEForceNodes>(ee_force_id);
  ee_motion_ = opt_vars->GetComponent<EEMotionNodes>(ee_motion_id);
  terrain_   = terrain;
  force_limit_ = force_limit;

  AddOptimizationVariables(opt_vars);

  int constraint_count = 0;
  for (int node_id=0; node_id<ee_force_->GetNodes().size(); ++node_id)
    if (ee_force_->IsStanceNode(node_id))
      constraint_count++; // positive normal force only allowed

  SetRows(constraint_count);
  SetName("Force-Constraint-" + ee_force_id);
}

VectorXd
ForceConstraint::GetValues () const
{
  VectorXd g(GetRows());

  int row=0;
  auto force_nodes = ee_force_->GetNodes();
  for (int node_id=0; node_id<force_nodes.size(); ++node_id) {
    if (ee_force_->IsStanceNode(node_id)) {

      int phase  = ee_force_->GetPhase(node_id);
      Vector3d p = ee_motion_->GetValueAtStartOfPhase(phase); // doesn't change during stance phase
      Vector3d n = terrain_->GetNormalizedBasis(HeightMap::Normal, p.x(), p.y());

      Vector3d f = force_nodes.at(node_id).at(kPos);
      g(row++) = f.transpose() * n; // >0 (unilateral forces)
    }
  }

  return g;
}

VecBound
ForceConstraint::GetBounds () const
{
  VecBound bounds;

  for (int i=0; i<ee_force_->GetNodes().size(); ++i)
    if (ee_force_->IsStanceNode(i))
      bounds.push_back(Bound(0.0, force_limit_)); // unilateral forces

  return bounds;
}

void
ForceConstraint::FillJacobianWithRespectTo (std::string var_set,
                                            Jacobian& jac) const
{
  if (var_set == ee_force_->GetName()) {

    int row = 0;
    for (int node_id=0; node_id<ee_force_->GetNodes().size(); ++node_id) {
      if (ee_force_->IsStanceNode(node_id)) {

        int phase  = ee_force_->GetPhase(node_id);
        Vector3d p = ee_motion_->GetValueAtStartOfPhase(phase); // doesn't change during phase
        Vector3d n = terrain_->GetNormalizedBasis(HeightMap::Normal, p.x(), p.y());

        for (auto dim : {X,Y,Z})
          jac.coeffRef(row, ee_force_->Index(node_id, kPos, dim)) = n(dim);

        row++;
      }
    }
  }


  if (var_set == ee_motion_->GetName()) {

    int row = 0;
    auto force_nodes = ee_force_->GetNodes();
    for (int force_node_id=0; force_node_id<force_nodes.size(); ++force_node_id) {
      if (ee_force_->IsStanceNode(force_node_id)) {

        int phase  = ee_force_->GetPhase(force_node_id);
        int ee_node_id = ee_motion_->GetNodeIDAtStartOfPhase(phase);

        Vector3d p = ee_motion_->GetValueAtStartOfPhase(phase); // doesn't change during pahse
        Vector3d f = force_nodes.at(force_node_id).at(kPos);

        for (auto dim : {X_,Y_}) {
          Vector3d dn_wrt_dim = terrain_->GetDerivativeOfNormalizedBasisWrt(HeightMap::Normal, dim, p.x(), p.y());
          jac.coeffRef(row, ee_motion_->Index(ee_node_id, kPos, dim)) = f.transpose()*dn_wrt_dim;
        }

        row++;
      }
    }
  }
}

ForceConstraint::~ForceConstraint ()
{
}

} /* namespace opt */
} /* namespace xpp */
