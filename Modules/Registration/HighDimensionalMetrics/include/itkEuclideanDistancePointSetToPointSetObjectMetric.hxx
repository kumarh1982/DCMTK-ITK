/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkEuclideanDistancePointSetToPointSetObjectMetric_hxx
#define __itkEuclideanDistancePointSetToPointSetObjectMetric_hxx

#include "itkEuclideanDistancePointSetToPointSetObjectMetric.h"

namespace itk
{

/** Constructor */
template<class TFixedPointSet, class TMovingPointSet>
EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::EuclideanDistancePointSetToPointSetObjectMetric()
{
}

/** Destructor */
template<class TFixedPointSet, class TMovingPointSet>
EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::~EuclideanDistancePointSetToPointSetObjectMetric()
{
}

template<class TFixedPointSet, class TMovingPointSet>
typename EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::MeasureType
EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::GetLocalNeighborhoodValue( const PointType & point ) const
{
  PointType closestPoint;
  closestPoint.Fill( 0.0 );

  if( this->GetGradientSource() == Superclass::GRADIENT_SOURCE_FIXED )
    {
    PointIdentifier pointId = this->m_MovingTransformedPointsLocator->
      FindClosestPoint( point );
    closestPoint = this->m_MovingTransformedPointSet->GetPoint( pointId );
    }
  else
    {
    PointIdentifier pointId = this->m_FixedTransformedPointsLocator->
      FindClosestPoint( point );
    closestPoint = this->m_FixedTransformedPointSet->GetPoint( pointId );
    }

  const MeasureType distance = point.EuclideanDistanceTo( closestPoint );
  return distance;
}

template<class TFixedPointSet, class TMovingPointSet>
typename EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::LocalDerivativeType
EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::GetLocalNeighborhoodDerivative( const PointType & point ) const
{
  PointType closestPoint;
  closestPoint.Fill( 0.0 );

  if( this->GetGradientSource() == Superclass::GRADIENT_SOURCE_FIXED )
    {
    PointIdentifier pointId = this->m_MovingTransformedPointsLocator->
      FindClosestPoint( point );
    closestPoint = this->m_MovingTransformedPointSet->GetPoint( pointId );
    }
  else
    {
    PointIdentifier pointId = this->m_FixedTransformedPointsLocator->
      FindClosestPoint( point );
    closestPoint = this->m_FixedTransformedPointSet->GetPoint( pointId );
    }

  const LocalDerivativeType localDerivative = closestPoint - point;
  return localDerivative;
}

template<class TFixedPointSet, class TMovingPointSet>
void
EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::GetLocalNeighborhoodValueAndDerivative( const PointType & point,
  MeasureType &measure, LocalDerivativeType & localDerivative ) const
{
  PointType closestPoint;
  closestPoint.Fill( 0.0 );

  if( this->GetGradientSource() == Superclass::GRADIENT_SOURCE_FIXED )
    {
    PointIdentifier pointId = this->m_MovingTransformedPointsLocator->
      FindClosestPoint( point );
    closestPoint = this->m_MovingTransformedPointSet->GetPoint( pointId );
    }
  else
    {
    PointIdentifier pointId = this->m_FixedTransformedPointsLocator->
      FindClosestPoint( point );
    closestPoint = this->m_FixedTransformedPointSet->GetPoint( pointId );
    }

  measure = point.EuclideanDistanceTo( closestPoint );
  localDerivative = closestPoint - point;
}

/** PrintSelf method */
template<class TFixedPointSet, class TMovingPointSet>
void
EuclideanDistancePointSetToPointSetObjectMetric<TFixedPointSet, TMovingPointSet>
::PrintSelf( std::ostream & os, Indent indent ) const
{
  Superclass::PrintSelf( os, indent );
}
} // end namespace itk

#endif
