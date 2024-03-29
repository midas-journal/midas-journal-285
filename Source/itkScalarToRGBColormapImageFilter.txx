/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkScalarToRGBColormapImageFilter.txx,v $
  Language:  C++
  Date:      $Date: $
  Version:   $Revision: $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkScalarToRGBColormapImageFilter_txx
#define _itkScalarToRGBColormapImageFilter_txx

#include "itkScalarToRGBColormapImageFilter.h"

#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkProgressReporter.h"

#include "itkRedColormapFunctor.h"
#include "itkGreenColormapFunctor.h"
#include "itkBlueColormapFunctor.h"
#include "itkGreyColormapFunctor.h"
#include "itkHotColormapFunctor.h"
#include "itkCoolColormapFunctor.h"
#include "itkSpringColormapFunctor.h"
#include "itkSummerColormapFunctor.h"
#include "itkAutumnColormapFunctor.h"
#include "itkWinterColormapFunctor.h"
#include "itkCopperColormapFunctor.h"
#include "itkHSVColormapFunctor.h"
#include "itkJetColormapFunctor.h"
#include "itkOverUnderColormapFunctor.h"

namespace itk
{

/**
 * Constructor
 */
template <class TInputImage, class TOutputImage>
ScalarToRGBColormapImageFilter<TInputImage, TOutputImage>
::ScalarToRGBColormapImageFilter()
{
  this->SetNumberOfRequiredInputs( 1 );

  this->m_UseInputImageExtremaForScaling = true;

  typedef Functor::GreyColormapFunctor<InputImagePixelType,
    OutputImagePixelType> DefaultColormapType;
  typename DefaultColormapType::Pointer greyColormap
    = DefaultColormapType::New();
  this->SetColormap( greyColormap );
}

/**
 * BeforeThreadedGenerateData
 */
template <class TInputImage, class TOutputImage>
void
ScalarToRGBColormapImageFilter<TInputImage,TOutputImage>
::BeforeThreadedGenerateData()
{
  if( this->m_UseInputImageExtremaForScaling == true )
    {
    ImageRegionConstIterator<InputImageType> It( this->GetInput(),
      this->GetInput()->GetRequestedRegion() );

    InputImagePixelType minimumValue
      = NumericTraits<InputImagePixelType>::max();
    InputImagePixelType maximumValue
      = NumericTraits<InputImagePixelType>::min();

    for( It.GoToBegin(); !It.IsAtEnd(); ++It )
      {
      InputImagePixelType value = It.Get();
      if( value < minimumValue )
        {
        minimumValue = value;
        }
      if( value > maximumValue )
        {
        maximumValue = value;
        }
      }

    this->GetColormap()->SetMinimumInputValue( minimumValue );
    this->GetColormap()->SetMaximumInputValue( maximumValue );
    }
}

/**
 * ThreadedGenerateData performs the pixel-wise mapping
 */
template <class TInputImage, class TOutputImage>
void
ScalarToRGBColormapImageFilter<TInputImage,TOutputImage>
::ThreadedGenerateData( const OutputImageRegionType &outputRegionForThread,
                        int threadId )
{
  InputImagePointer  inputPtr = this->GetInput();
  OutputImagePointer outputPtr = this->GetOutput();

  // Define the portion of the input to walk for this thread, using
  // the CallCopyOutputRegionToInputRegion method allows for the input
  // and output images to be different dimensions
  InputImageRegionType inputRegionForThread;
  this->CallCopyOutputRegionToInputRegion(inputRegionForThread,
    outputRegionForThread);

  // Define the iterators
  ImageRegionConstIterator<TInputImage> inputIt(inputPtr, inputRegionForThread);
  ImageRegionIterator<TOutputImage> outputIt(outputPtr, outputRegionForThread);

  ProgressReporter progress( this, threadId,
    outputRegionForThread.GetNumberOfPixels());

  inputIt.GoToBegin();
  outputIt.GoToBegin();

  while( !inputIt.IsAtEnd() )
    {
    outputIt.Set( this->m_Colormap->operator()( inputIt.Get() ) );
    ++inputIt;
    ++outputIt;
    progress.CompletedPixel();  // potential exception thrown here
    }
}

template <class TInputImage, class TOutputImage>
void
ScalarToRGBColormapImageFilter<TInputImage,TOutputImage>
::SetColormap( ColormapEnumType map )
{
  switch( map )
    {
    case Red:
      {
      typedef Functor::RedColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Green:
      {
      typedef Functor::GreenColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Blue:
      {
      typedef Functor::BlueColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Grey: default:
      {
      typedef Functor::GreyColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Hot:
      {
      typedef Functor::HotColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Cool:
      {
      typedef Functor::CoolColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Spring:
      {
      typedef Functor::SpringColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Summer:
      {
      typedef Functor::SummerColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Autumn:
      {
      typedef Functor::AutumnColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Winter:
      {
      typedef Functor::WinterColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Copper:
      {
      typedef Functor::CopperColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case Jet:
      {
      typedef Functor::JetColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case HSV:
      {
      typedef Functor::HSVColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    case OverUnder:
      {
      typedef Functor::OverUnderColormapFunctor<InputImagePixelType,
        OutputImagePixelType> ColormapType;
      typename ColormapType::Pointer colormap = ColormapType::New();
      this->SetColormap( colormap );
      break;
      }
    }

}


} // end namespace itk

#endif
