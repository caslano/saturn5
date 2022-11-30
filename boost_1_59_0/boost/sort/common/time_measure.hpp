//----------------------------------------------------------------------------
/// @file time_measure.hpp
/// @brief This class is done in order to simplify the time measure in the
///        benchmaark programs
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_TOOLS_TIME_MEASURE_HPP
#define __BOOST_SORT_PARALLEL_TOOLS_TIME_MEASURE_HPP

#include <chrono>

namespace boost       
{
namespace sort        
{
namespace common      
{

namespace chrn = std::chrono;
//
//***************************************************************************
//                D E F I N I T I O N S
//***************************************************************************
typedef chrn::steady_clock::time_point           time_point;

time_point now ( );
double subtract_time  ( const time_point & t1, const time_point & t2 );
//
//---------------------------------------------------------------------------
//  function : now
/// @brief return the time system in a internal format ( steady_clock)
/// @return time in steady_clock format
//---------------------------------------------------------------------------
time_point now ( ) {   return chrn::steady_clock::now( ); };
//
//---------------------------------------------------------------------------
//  function : subtract_time
/// @brief return the time in double format
/// @param [in] t1 : first  time in time_point format
/// @param [in] t2 : second time in time_point format
/// @return time in seconds of the difference of t1 - t2
//---------------------------------------------------------------------------
double subtract_time  ( const time_point & t1, const time_point & t2 )
{   //------------------------ begin ---------------------------------
    chrn::duration<double> time_span =
                chrn::duration_cast < chrn::duration < double > > ( t1 - t2 );
    return  time_span.count( );
};

//***************************************************************************
};//    End namespace benchmark
};//    End namespace sort
};//    End namespace boost
//***************************************************************************
#endif

/* time_measure.hpp
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
*/