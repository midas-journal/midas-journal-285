/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkJetColormapFunctor.h,v $
  Language:  C++
  Date:      $Date: $
  Version:   $Revision: $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkJetColormapFunctor_h
#define __itkJetColormapFunctor_h

#include "itkColormapFunctor.h"

namespace itk {

namespace Functor {  

/**
 * \class JetColormapFunctor
 * \brief Function object which maps a scalar value into an RGB colormap value.
 *
 */
template< class TScalar, class TRGBPixel >
class ITK_EXPORT JetColormapFunctor
: public ColormapFunctor<TScalar, TRGBPixel>
{
public:
  JetColormapFunctor() {};
  ~JetColormapFunctor() {};

  typedef JetColormapFunctor                     Self;
  typedef ColormapFunctor<TScalar, TRGBPixel>    Superclass;
  typedef SmartPointer<Self>                     Pointer;
  typedef SmartPointer<const Self>               ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  typedef typename Superclass::RGBPixelType      RGBPixelType;
  typedef typename Superclass::ScalarType        ScalarType;  
  typedef typename Superclass::RealType          RealType;
  
  virtual RGBPixelType operator()( const TScalar & ) const;

};
  
} // end namespace functor

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkJetColormapFunctor.txx"
#endif

#endif
