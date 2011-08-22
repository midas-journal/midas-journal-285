#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRGBPixel.h"
#include "itkRGBAPixel.h"

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
#include "itkCustomColormapFunctor.h"
#include "itkOverUnderColormapFunctor.h"

#include "itkScalarToRGBColormapImageFilter.h"

#include <fstream.h>
#include <sstream>
#include <string>

int itkScalarToRGBColormapImageFilterTest( int argc, char *argv[] )
{
  const unsigned int ImageDimension = 2;

  typedef unsigned int PixelType;
  typedef itk::RGBPixel<unsigned char> RGBPixelType;
//  typedef itk::RGBAPixel<unsigned char> RGBPixelType;

  typedef itk::Image<PixelType, ImageDimension> ImageType;
  typedef itk::Image<float, ImageDimension> RealImageType;
  typedef itk::Image<RGBPixelType, ImageDimension> RGBImageType;

  typedef itk::ImageFileReader<ImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  std::string colormapString( argv[3] );

  typedef itk::ScalarToRGBColormapImageFilter<ImageType,
    RGBImageType> RGBFilterType;
  RGBFilterType::Pointer rgbfilter = RGBFilterType::New();
  rgbfilter->SetInput( reader->GetOutput() );

  if ( colormapString == "red" )
    {
    rgbfilter->SetColormap( RGBFilterType::Red );
    }
  else if ( colormapString == "green"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Green );
    }
  else if ( colormapString == "blue"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Blue );
    }
  else if ( colormapString == "grey"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Grey );
    }
  else if ( colormapString == "cool"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Cool );
    }
  else if ( colormapString == "hot"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Hot );
    }
  else if ( colormapString == "spring"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Spring );
    }
  else if ( colormapString == "autumn"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Autumn );
    }
  else if ( colormapString == "winter"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Winter );
    }
  else if ( colormapString == "copper"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Copper );
    }
  else if ( colormapString == "summer"  )
    {
    rgbfilter->SetColormap( RGBFilterType::Summer );
    }
  else if ( colormapString == "jet"  )
    {
//    rgbfilter->SetColormap( RGBFilterType::Jet );
    typedef itk::Functor::JetColormapFunctor<ImageType::PixelType,
      RGBImageType::PixelType> ColormapType;
    ColormapType::Pointer colormap = ColormapType::New();
    rgbfilter->SetColormap( colormap );
    }
  else if ( colormapString == "hsv"  )
    {
//    rgbfilter->SetColormap( RGBFilterType::HSV );
    typedef itk::Functor::HSVColormapFunctor<ImageType::PixelType,
      RGBImageType::PixelType> ColormapType;
    ColormapType::Pointer colormap = ColormapType::New();
    rgbfilter->SetColormap( colormap );
    }
  else if ( colormapString == "overunder"  )
    {
    rgbfilter->SetColormap( RGBFilterType::OverUnder );
    }
  else if ( colormapString == "custom"  )
    {
    typedef itk::Functor::CustomColormapFunctor<ImageType::PixelType,
      RGBImageType::PixelType> ColormapType;
    ColormapType::Pointer colormap = ColormapType::New();

    ifstream str( argv[4] );
    std::string line;

    // Get red values
    {
    std::getline( str, line );
    std::istringstream iss( line );
    float value;
    ColormapType::ChannelType channel;
    while ( iss >> value )
      {
      channel.push_back( value );
      }
    colormap->SetRedChannel( channel );
    }

    // Get green values
    {
    std::getline( str, line );
    std::istringstream iss( line );
    float value;
    ColormapType::ChannelType channel;
    while ( iss >> value )
      {
      channel.push_back( value );
      }
    colormap->SetGreenChannel( channel );
    }
    // Get blue values
    {
    std::getline( str, line );
    std::istringstream iss( line );
    float value;
    ColormapType::ChannelType channel;
    while ( iss >> value )
      {
      channel.push_back( value );
      }
    colormap->SetBlueChannel( channel );
    }
    rgbfilter->SetColormap( colormap );
    }

  rgbfilter->GetColormap()->SetMinimumRGBComponentValue( 0 );
  rgbfilter->GetColormap()->SetMaximumRGBComponentValue( 255 );

  try
    {
    rgbfilter->Update();
    }
  catch (...)
    {
    return EXIT_FAILURE;
    }
    
  typedef itk::ImageFileWriter<RGBImageType> WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( rgbfilter->GetOutput() );
  writer->Update();
  
  return EXIT_SUCCESS;
}

int main( int argc, char *argv[] )
{
  if ( argc < 4 )
    {
    std::cout << "Usage: " << argv[0] <<
      " inputImage outputImage colormap [customColormapFile]" << std::endl;
    std::cout <<
      "  Possible colormaps: grey, red, green, blue, copper, jet, hsv, ";
    std::cout <<
      "spring, summer, autumn, winter, hot, cool, custom" << std::endl;
    return EXIT_FAILURE;
    }

  return itkScalarToRGBColormapImageFilterTest( argc, argv );
}
