/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef __itkBalloonForceFilter_h
#define __itkBalloonForceFilter_h

#include "itkMeshToMeshFilter.h"
#include "vnl/vnl_matrix_fixed.h"
#include "vnl/vnl_math.h"
#include "itkMesh.h"
#include "itkVector.h"
#include "itkTriangleCell.h"
#include "itkImage.h"

namespace itk
{

/** \class BalloonForceFilter
 * \brief 
 *
 * BalloonForceFilter is used to apply balloon force and the potential
 * force onto the deformable model.
 * The balloon force is vertical to the surface of the model. The potential 
 * force is given out by the estimated boundary points. These two will meet 
 * a balance at the boundary, thus the deformable model will fit to the 
 * boundary.
 * Users should use deformable model as input using setInput and also provide
 * the filter with a potential image which will provide the estimated bounday.
 * The image should be a binary image with object and background labelled 
 * differently. These image can be given by GibbsPriorFilter or any other
 * segmentation filters.
 * When the nodes on the model stopped at the estimated boundary, using the
 * GapSearch method to add new nodes at region the object has a complicate
 * shape.
 */
template <class TInputMesh, class TOutputMesh>
class ITK_EXPORT BalloonForceFilter : public MeshToMeshFilter<TInputMesh, TOutputMesh>
{
public:
  /**
   * Standard "Self" typedef.
   */
  typedef BalloonForceFilter  Self;

  /**
   * Standard "Superclass" typedef.
   */
  typedef MeshToMeshFilter<TInputMesh, TOutputMesh> Superclass;

  /** 
   * Smart pointer typedef support 
   */
  typedef SmartPointer<Self>  Pointer;

  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);
  
  /** 
   * Run-time type information (and related methods).
   */
  itkTypeMacro(BalloonForceFilter,MeshToMeshFilter);

  /** 
   * Some typedefs.
   */
  typedef TInputMesh InputMeshType;
  typedef typename InputMeshType::PointsContainerPointer
      InputPointsContainerPointer;
  typedef typename typename InputMeshType::PointsContainer::Iterator
      InputPointsContainerIterator;
  typedef typename InputMeshType::PointDataContainerPointer
      InputPointDataContainerPointer;
  typedef typename typename InputMeshType::PointDataContainer::Iterator
      InputPointDataContainerIterator;
  typedef typename InputMeshType::CellsContainerPointer
      InputCellsContainerPointer;
  typedef typename typename InputMeshType::CellsContainer::Iterator
      InputCellsContainerIterator;
  typedef typename InputMeshType::CellDataContainerPointer
      InputCellDataContainerPointer;
  typedef typename typename InputMeshType::CellDataContainer::Iterator
      InputCellDataContainerIterator;

  typedef itk::Image<unsigned short, 3> ImageType;
  typedef typename InputMeshType::Pointer InputMeshPointer;
  typedef typename ImageType::Pointer ImagePointer;
  typedef typename ImageType::IndexType IndexType;

  typedef itk::Vector<float, 3>				FloatVector;
  typedef itk::Vector<int, 3>				IntVector;

  typedef typename InputMeshType::Cell			Cell;
  typedef typename InputMeshType::CellTraits	CellTraits;
  typedef itk::TriangleCell<float, CellTraits>	TriCell;
  typedef typename InputMeshType::PointType		IPT;
  typedef typename InputMeshType::PixelType		PT;

  /** 
   * Some functions.
   */
  void ComputeForce();
  void Initialize();
  void SetStiffnessMatrix();
  void Advance();
  void SetStiffness(double a, double b);
  void SetResolution(int a, int b, int c);
  void SetCenter(int a, int b, int c);
  void Reset();
  void ComputeDt();
  void ComputeOutput();
  void SetForces(TInputMesh* force);
  void SetLocations(TInputMesh* location);
  void SetNormals(TInputMesh* normals);
  void SetDisplacements(TInputMesh* displace);
  void SetDerives(TInputMesh* derive);
  void SetPotential(ImagePointer potential);
  void NodeAddition(int i);
  void GapSearch();

protected:
  BalloonForceFilter();
  ~BalloonForceFilter() {};
  BalloonForceFilter(const BalloonForceFilter&) {};
  void operator=(const BalloonForceFilter&) {};
//  void PrintSelf(std::ostream& os, Indent indent);

/** 
 * These meshes are defined to hold the vectors as force, etc.
 */
  InputMeshPointer m_Forces; 
  InputMeshPointer m_Normals;
  InputMeshPointer m_Displacements;
  InputMeshPointer m_Derives;
  InputMeshPointer m_Locations;
  InputMeshPointer m_Input;
  InputMeshPointer m_Output;

  /** 
   * Three different kinds of stiffness matrix.
   */
  vnl_matrix_fixed<double, 4, 4> NStiffness;
  vnl_matrix_fixed<double, 4, 4> SStiffness;
  vnl_matrix_fixed<double, 4, 4> CStiffness;
  vnl_matrix_fixed<double, 4, 4> **K;
  
  double	m_Stiffness[2];
  double	TimeStep;
  int		m_Resolution[3];
  IndexType	m_Center;
  float		m_MiniT;
  int		m_Step;
  int		m_NumNodes;
  int		m_NumCells;
  int		m_NumNewNodes;
  float		m_NewNodes[200][4];

  ImagePointer		m_Potential;
  unsigned short	m_ObjectLabel;
  
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBalloonForceFilter.txx"
#endif

#endif
