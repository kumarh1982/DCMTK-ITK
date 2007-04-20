/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkBayesianClassifierImageFilter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkBayesianClassifierImageFilter_h
#define __itkBayesianClassifierImageFilter_h

#include "itkVectorImage.h"
#include "itkImageToImageFilter.h"
#include "itkMaximumDecisionRule.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

namespace itk
{
  
/** \class BayesianClassifierImageFilter
 *
 * \brief Performs Bayesian Classification on an image.
 *
 * \par Inputs and Outputs
 * The input to this filter is an itk::VectorImage that represents pixel
 * memberships to 'n' classes. This image is conveniently generated by the 
 * BayesianClassifierInitializationImageFilter. You may use that filter to
 * generate the membership images or specify your own.
 *
 * \par
 * The output of the filter is a label map (an image of unsigned char's is the
 * default.) with pixel values indicating the classes they correspond to. Pixels 
 * with intensity 0 belong to the 0th class, 1 belong to the 1st class etc.... 
 * The classification is done by applying a Maximum decision rule to the posterior 
 * image.
 *
 * \par Parameters
 * The filter optionally allows you to specify a prior image as well. The prior 
 * image, if specified must be a VectorImage with as many components as the 
 * number of classes. The posterior image is then generated by multiplying the 
 * prior image with the membership image. If the prior image is not specified, 
 * the posterior image is the same as the membership image. Another way to 
 * look at it is that the priors default to having a uniform distribution over 
 * the number of classes.
 * Posterior membership of a pixel = Prior * Membership
 *
 * \par
 * The filter optionally accepts a smoothing filter and number of iterations
 * associated with the smoothing filter.
 * The philosophy is that the filter allows you to iteratively
 * smooth the posteriors prior to applying the decision rule. It is hoped
 * that this would yield a better classification. The user will need to plug
 * in his own smoothing filter with all the parameters set. 
 *
 * \par Template parameters
 * InputVectorImage, datatype of the output labelmap, precision of the posterior
 * image, precision of the prior image.
 *
 * \author John Melonakos, Georgia Tech
 *
  * \note
 * This work is part of the National Alliance for Medical Image Computing 
 * (NAMIC), funded by the National Institutes of Health through the NIH Roadmap
 * for Medical Research, Grant U54 EB005149.
 * 
 * \sa VectorImage
 * \sa BayesianClassifierInitializationImageFilter
 * \ingroup ClassificationFilters 
 */
template < class TInputVectorImage, class TLabelsType=unsigned char, 
           class TPosteriorsPrecisionType=double, class TPriorsPrecisionType=double >
class ITK_EXPORT BayesianClassifierImageFilter :
    public ImageToImageFilter< 
              TInputVectorImage, Image< TLabelsType, 
              ::itk::GetImageDimension< TInputVectorImage >::ImageDimension > >
{
public:
  /** Standard class typedefs. */
  typedef BayesianClassifierImageFilter     Self;
  typedef ImageToImageFilter< 
    TInputVectorImage,
    Image< TLabelsType, 
           ::itk::GetImageDimension< 
    TInputVectorImage >::ImageDimension > > Superclass;
  typedef SmartPointer<Self>                Pointer;
  typedef SmartPointer<const Self>          ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( BayesianClassifierImageFilter, ImageToImageFilter );

  /** Input and Output image types */
  typedef typename Superclass::InputImageType        InputImageType;
 
  /** Dimension of the input image */
  itkStaticConstMacro( Dimension, unsigned int, 
                       ::itk::GetImageDimension< InputImageType >::ImageDimension );

  typedef Image< TLabelsType, 
          itkGetStaticConstMacro(Dimension) >        OutputImageType;
  typedef typename InputImageType::ConstPointer      InputImagePointer;
  typedef typename OutputImageType::Pointer          OutputImagePointer;
  typedef typename InputImageType::RegionType        ImageRegionType;
  
  /** Input and Output image iterators */
  typedef ImageRegionConstIterator< InputImageType > InputImageIteratorType;
  typedef ImageRegionIterator< OutputImageType >     OutputImageIteratorType;

  /** Pixel types. */
  typedef typename InputImageType::PixelType              InputPixelType;
  typedef typename OutputImageType::PixelType             OutputPixelType;

  /** Image Type and Pixel type for the images representing the Prior
   * probability of a pixel belonging to  a particular class. This image has
   * arrays as pixels, the number of elements in the array is the same as the
   * number of classes to be used.  */
  typedef VectorImage< TPriorsPrecisionType, 
     itkGetStaticConstMacro(Dimension) >                  PriorsImageType;
  typedef typename PriorsImageType::PixelType             PriorsPixelType;
  typedef typename PriorsImageType::Pointer               PriorsImagePointer;
  typedef ImageRegionConstIterator< PriorsImageType >     PriorsImageIteratorType;

  /** Image Type and Pixel type for the images representing the membership of a
   *  pixel to a particular class. This image has arrays as pixels, the number of 
   *  elements in the array is the same as the number of classes to be used.    */
  typedef TInputVectorImage                               MembershipImageType;
  typedef typename MembershipImageType::PixelType         MembershipPixelType;
  typedef typename MembershipImageType::Pointer           MembershipImagePointer;
  typedef ImageRegionConstIterator< MembershipImageType > MembershipImageIteratorType;

  /** Image Type and Pixel type for the images representing the Posterior
   * probability of a pixel belonging to  a particular class. This image has
   * arrays as pixels, the number of elements in the array is the same as the
   * number of classes to be used.  */
  typedef VectorImage< TPosteriorsPrecisionType, 
     itkGetStaticConstMacro(Dimension) >                  PosteriorsImageType;
  typedef typename PosteriorsImageType::PixelType         PosteriorsPixelType;
  typedef typename PosteriorsImageType::Pointer           PosteriorsImagePointer;
  typedef ImageRegionIterator< PosteriorsImageType >      PosteriorsImageIteratorType;

  /** Decision rule to use for defining the label */
  typedef MaximumDecisionRule                             DecisionRuleType;
  typedef DecisionRuleType::Pointer                       DecisionRulePointer;

  /** An image from a single component of the Posterior */
  typedef itk::Image< TPosteriorsPrecisionType, 
       itkGetStaticConstMacro(Dimension) >                ExtractedComponentImageType;
  
  /** Optional Smoothing filter that will be applied to the Posteriors */
  typedef ImageToImageFilter< 
                   ExtractedComponentImageType, 
                   ExtractedComponentImageType  >         SmoothingFilterType;
  typedef typename SmoothingFilterType::Pointer           SmoothingFilterPointer;

  /** Set/ Get macros for the smoothing filter that may optionally be applied
   * to the posterior image */
  void SetSmoothingFilter( SmoothingFilterType * );
  itkGetMacro( SmoothingFilter, SmoothingFilterPointer );

  /** Number of iterations to apply the smoothing filter */
  itkSetMacro( NumberOfSmoothingIterations, unsigned int );
  itkGetMacro( NumberOfSmoothingIterations, unsigned int );

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(UnsignedIntConvertibleToLabelsCheck,
    (Concept::Convertible<unsigned int, TLabelsType>));
  itkConceptMacro(PosteriorsAdditiveOperatorsCheck,
    (Concept::AdditiveOperators<TPosteriorsPrecisionType>));
  itkConceptMacro(IntConvertibleToPosteriorsCheck,
    (Concept::Convertible<int, TPosteriorsPrecisionType>));
  itkConceptMacro(InputHasNumericTraitsCheck,
    (Concept::HasNumericTraits<typename InputPixelType::ValueType>));
  itkConceptMacro(PosteriorsHasNumericTraitsCheck,
    (Concept::HasNumericTraits<TPosteriorsPrecisionType>));
  itkConceptMacro(PriorsHasNumericTraitsCheck,
    (Concept::HasNumericTraits<TPriorsPrecisionType>));
  itkConceptMacro(InputPriorsPosteriorsMultiplyOperatorCheck,
    (Concept::MultiplyOperator<typename InputPixelType::ValueType,
                               PriorsPixelType, PosteriorsPixelType>));
  /** End concept checking */
#endif

protected:

  BayesianClassifierImageFilter();
  virtual ~BayesianClassifierImageFilter() {}
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** Here is where the classification is computed. */
  virtual void GenerateData();

  /** Allocate Memory for the Output. */
  virtual void AllocateOutputs();


  /** Methods for computing the labeled map for all combinations of conditions */
  virtual void ComputeBayesRule();
  virtual void NormalizeAndSmoothPosteriors();
  virtual void ClassifyBasedOnPosteriors();
  PosteriorsImageType *GetPosteriorImage();

private:

  BayesianClassifierImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** Boolean flag indicating that the user defined the Priors optional input */
  bool m_UserProvidedPriors;

  /** Boolean flag indicating that the user provided a Smoothing filter */
  bool m_UserProvidedSmoothingFilter;

  /** Pointer to optional Smoothing filter */
  SmoothingFilterPointer  m_SmoothingFilter;

  /** Number of iterations to apply the smoothing filter */
  unsigned int m_NumberOfSmoothingIterations;

};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBayesianClassifierImageFilter.txx"
#endif

#endif
