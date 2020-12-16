// ----------------------------------------------------------------------------
// workarounds_stlport.hpp : workaround STLport issues
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_MACROS_STLPORT_HPP
#define BOOST_MACROS_STLPORT_HPP

// *** This should go to "boost/config/stdlib/stlport.hpp".

// If the streams are not native and there are problems with using templates
// accross namespaces, we define some macros to enable a workaround for this.

// STLport 4.5
#if !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif

// STLport 4.0
#if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_OWN_NAMESPACE) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif


// ----------------------------------------------------------------------------

#endif // BOOST_MACROS_STLPORT_HPP

/* workarounds_stlport.hpp
fyn4HwF/e/A3AP848G8L/j/B/wr4rwX/JPA/Cf4jwf8E+A8F/6/g3xv8/cC/APzXg/8/wH8J+G8E//ngvwz85eC/H/y3g/8P8J8G/q3AvwP4dwH/T+B/GvydwH85+D8C/zfgPwj8r4K/A/jXBX8j8D8G/i3B/xD4m4P/TPCvCP5zwb8y+NcC/3Twvw/+z8G/NfhvAX8V+FcB/1Hg3w78G4J/I/CXgH8f8M8C/zDwdwP/y+CfDf7W4P8A/O3AfzT4h4P/edL/gXYvwZ8N/t/BfzP49wX/geB/Cvz3gn8n8O8G/oHgHwX+58A/D/xfg/8a8P8G/j7gHwT+7cF/DPhzwP8L+BuC/3DwDwX/zuC/CPxXgX8P8F8K/p7gPwX8/wb/BeDvAv4fwH83+G8D/+vg3xz8zcC/EPzfgf8F8D8D/tXAvzb4vwD/aPCfBf6+4F8f/A+D/0rwHwb+7uDPB//+4N8A/BXgHwP+I8A/BPxvgn8L8G8D/pngPx78u4L/K/DPBf864H8b/AeAf1XwvwH+d8HfEfxdwd8E/APAvxL4W4B/P/A/CP4XwX8d+MeC/1TwnwH+D8E/FfyfgP9x8O8I/ongPwn8L4F/MPivBn8x+PcE//fg/wz8BeA/GPw3gL8x+O8E/xTwtwR/W/BvDP4rwH8r+B8F/3zwvwX+SvBvBv7dwX8P+GeA/1/gLwN/D/DPAX8h+PuDfwXw/wj+NcCfC/7O4N8L/HeA/1jwPwD+TcB/IfjfA//P4D8b/GuCvwj8r4H/ZPCfDv7zwL8p+I8D/6fgfxb8I8HfCvzvgP9E8F8M/hPAvzr47wP/x+DvDf7x4O8F/nPA3wb8TcF/E/hHgP8u8K8H/jzwHwL+yeCfVogAAPwTwF8K/kfA3x78DcA/Dvzbgv9P8L8ShAAA/JPA/yT4j5yAAAD8h4L/V/DvDf5+4F/ghQAgGwEA+C/hIABoiQAgHAEA+MvBf78KAQD4/wD/aYEIAMC/wzAEAOD/aRQCgHgEAOC//DwCAPB/A/6DwP8q+DuAf13wNwL/Y+DfEvwPgb85+M8E/4p2CADAv7IFAgDwTwf/++D/PBgBwHAEAOCvAv8q4D8qCgEA+DcE/0bgLwH/PuCfBf5h4O+2HQEA+GeDvzX4PwB/O/AfDf7h4E/6P4AAwBMBAPh/T0UAAP59wX/gJAQAcQgAwL/TdAQA4B8I/lHgfw7888D/dQgCAPD/Bv4+4B8E/u3Bfwz4c54iAAB/Q/AfDv6h4N/ZEgEA+K9aggCgPwIA8PesiAAA/P9ujgAA/F3eIADgIQAA/23gfx38m4O/GfgX/kAAAP4XwP8M+FcD/9qHEACAf7QzAgDw9wX/+tMQAEQiAAD/YeDvDv78nQgAwL8B+CvAPwb8R4B/CPjf9EUAAP5twD+zKgIA8O96DAEA+OdaIQAA/9vgPwD8q4L/jRsIAMDfUYkAAPxNwD8A/Cv5IwDIRQAA/gfB/yL4rzuMAKATAgAHBADg/xD8Uy8hAMhAACBBAAD+iQYIAMD/EvgHByAAAH8x+PcE//fnEACAvwD8B/shAAB/Y/DfCf4p4G8J/rYuCAB6IQBQIAAA/6Pgnw/+t/IRAIB/s5kIALgIAMA/wxQBAPjLhiAAAP8c8BeCvz/4VwD/j+BfA/y54O8M/r3Af0d9BADgf8AVAUBrBADgf+85AgDwn90CAcAFBADgf60yAgDwnw7+8zojAKiLAAD8n45DAAD+keBvBf53KiAAAP/F4D8B/KsLEACA/2Pw9wb/ePD3Av854G8D/qZpCADAPyIRAQD41wtd+b5HuMBr2KFl9RvOHNDa9VTCWrc3nAXN1kZ9XTetwoPukV/t2R8Tk9Y=
*/