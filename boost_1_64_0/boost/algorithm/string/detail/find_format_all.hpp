//  Boost string_algo library find_format_all.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_ALL_DETAIL_HPP
#define BOOST_STRING_FIND_FORMAT_ALL_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/algorithm/string/detail/find_format_store.hpp>
#include <boost/algorithm/string/detail/replace_storage.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

// find_format_all_copy (iterator variant) implementation ---------------------------//

           template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline OutputIteratorT find_format_all_copy_impl2(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult )
            {       
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::boost::begin(Input);

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    Output = std::copy( LastMatch, M.begin(), Output );
                    // Copy formatted result
                    Output = std::copy( ::boost::begin(M.format_result()), ::boost::end(M.format_result()), Output );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::boost::end(Input) );
                }

                // Copy the rest of the sequence
                Output = std::copy( LastMatch, ::boost::end(Input), Output );

                return Output;
            }

            template< 
                typename OutputIteratorT,
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline OutputIteratorT find_format_all_copy_impl(
                OutputIteratorT Output,
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult )
            {   
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_all_copy_impl2( 
                        Output,
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return std::copy( ::boost::begin(Input), ::boost::end(Input), Output );
                }
            }

 // find_format_all_copy implementation ----------------------------------------------//

           template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline InputT find_format_all_copy_impl2(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult,
                const FormatResultT& FormatResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_const_iterator<InputT>::type input_iterator_type; 

                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );

                // Initialize last match
                input_iterator_type LastMatch=::boost::begin(Input);

                // Output temporary
                InputT Output;

                // Iterate through all matches
                while( M )
                {
                    // Copy the beginning of the sequence
                    boost::algorithm::detail::insert( Output, ::boost::end(Output), LastMatch, M.begin() );
                    // Copy formatted result
                    boost::algorithm::detail::insert( Output, ::boost::end(Output), M.format_result() );

                    // Proceed to the next match
                    LastMatch=M.end();
                    M=Finder( LastMatch, ::boost::end(Input) );
                }

                // Copy the rest of the sequence
                ::boost::algorithm::detail::insert( Output, ::boost::end(Output), LastMatch, ::boost::end(Input) );

                return Output;
            }

            template< 
                typename InputT, 
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline InputT find_format_all_copy_impl(
                const InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                const FindResultT& FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    return ::boost::algorithm::detail::find_format_all_copy_impl2(
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                } else {
                    return Input;
                }
            }

 // find_format_all implementation ------------------------------------------------//
        
            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT,
                typename FormatResultT >
            inline void find_format_all_impl2( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult,
                FormatResultT FormatResult)
            {
                typedef BOOST_STRING_TYPENAME 
                    range_iterator<InputT>::type input_iterator_type; 
                typedef find_format_store<
                        input_iterator_type, 
                        FormatterT,
                        FormatResultT > store_type;

                // Create store for the find result
                store_type M( FindResult, FormatResult, Formatter );
          
                // Instantiate replacement storage
                std::deque<
                    BOOST_STRING_TYPENAME range_value<InputT>::type> Storage;

                // Initialize replacement iterators
                input_iterator_type InsertIt=::boost::begin(Input);
                input_iterator_type SearchIt=::boost::begin(Input);
                
                while( M )
                {
                    // process the segment
                    InsertIt=process_segment( 
                        Storage,
                        Input,
                        InsertIt,
                        SearchIt,
                        M.begin() );
                    
                    // Adjust search iterator
                    SearchIt=M.end();

                    // Copy formatted replace to the storage
                    ::boost::algorithm::detail::copy_to_storage( Storage, M.format_result() );

                    // Find range for a next match
                    M=Finder( SearchIt, ::boost::end(Input) );
                }

                // process the last segment
                InsertIt=::boost::algorithm::detail::process_segment( 
                    Storage,
                    Input,
                    InsertIt,
                    SearchIt,
                    ::boost::end(Input) );
                
                if ( Storage.empty() )
                {
                    // Truncate input
                    ::boost::algorithm::detail::erase( Input, InsertIt, ::boost::end(Input) );
                }
                else
                {
                    // Copy remaining data to the end of input
                    ::boost::algorithm::detail::insert( Input, ::boost::end(Input), Storage.begin(), Storage.end() );
                }
            }

            template<
                typename InputT,
                typename FinderT,
                typename FormatterT,
                typename FindResultT >
            inline void find_format_all_impl( 
                InputT& Input,
                FinderT Finder,
                FormatterT Formatter,
                FindResultT FindResult)
            {
                if( ::boost::algorithm::detail::check_find_result(Input, FindResult) ) {
                    ::boost::algorithm::detail::find_format_all_impl2(
                        Input,
                        Finder,
                        Formatter,
                        FindResult,
                        Formatter(FindResult) );
                }
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost

#endif  // BOOST_STRING_FIND_FORMAT_ALL_DETAIL_HPP

/* find_format_all.hpp
1Aj0Lm70F76Qlk/zFL41iKlOJGZlKKIh32gkuPG8eu/KK/y0hO6mg9uOoFQv6+tUPPR9/Mmsthqsdj3R4lJP9yNWu743FDCOe0+LA5+D0em9nRBwZ3/lmD/VjvnSdhRZm2fXOObfYKdCvsUgO/O3kEUzdop2G2+a+wrfUn87KULH3RoAxNRhcvJrxHu56ciydaFpuzofAT9ZTIIgVf1SfAxZK2R8ReYImWTKEGzbUz2PaDc9IugLTkiz+UJv5uDk3v65sQawQW8IHtprulSoLt2riRO4GjYwD0Dd+xBTKFAFw5kPzN2GCoDDbXTcu5A4wT5wgvnECfoTJ5B5ba/wgtNxNm929e3xfrC6G40VTVldpZ9YnRdUgIVwxozysdZ7tRwDhge+Ao0HsYGYnf3AC2L0dE+kL39MMhJcyTrOm+zLXjYdK8O73uw1M7ozCnA7lpeEHPtyb2gxGqFHpg0g07dyXZlqj7GCa+wWD3K3DpPqNtqoujkmR3czS7+DQhZP7+oHT/cKT39z0rXuA5g65CK0cUaFH/K8ydVRxo/g6D4sYmDqPf0ZX3rB1GlTkLGauGe4/fqhll1NhrfVFtjOPj7h6wBCl6zSBTZeiuVCOq/CPPfSsI835VKygQo+JDnQKCWdIZrSOyRYIqKGTMMGT/cN3uyPZoz0Bzt28WbUjr0Pb+XF5gV/biNv98ay4npbwzvBfGQBfMXWLt1XN3zQfbknCa62uq9oWB2q7F6PJ4VDSHTjLQD8JO2AZ/2G9XiMwNN9Pa9Qf86Zu6LovGCuLcdo9GTs9vTGofuMIWWPaLnkc5FLPvp1pBhz/iW0vOM9QwusXsBeiQDbpNoBjNhBLeyhabIXrvba1+UVLlW3/yU+hvO7S7+WuTgDGakplo+jCbpTIscjkqxZ/k6RxtLaM6zitGX2gIjinlWP45i09tniavYTsUkvJDlgecSOsmzsmJzoNG1g/q33vv9X/5zLg+5QwzsYWhi03Ssa1jdp0oOnyh/iGzYYFVY8Bu5yDNXu5UmIa+ab5POUy2SBGi6b1YeH6BdiP2WzNx9G217nLhp4cPG0ARv/i2NwoWLm2RgwMx9OsoTz4LDx7Dcp93o1JpsHGO1mMTiuYlmDDA/4HLbfIFYIZ1I+Nwmw42XwnfcwHds/iqG3X6U1iwCZr+Ti26L4FNbXDxzE1+hntjHvBNT+hST1TPXEqZhSeusaYoG4ml+xVR3Ha5OuU/iXFt557CwX31QEmeV9M5BNBOWkTgwFMX3u/1VSDNkLFtbTHvDVDrT2v86ZgV055lxv0/c2iGNxwcOJKz/EcgR4W1Eh/eOnf86H05CiDkTzOD6wm4x/ay4ENN5EN1aiS8g4AxweIfZYY0B/UNsLSRKNmOd7IqZbZMyHZyImOTLmqQLZVRBPIKFwHruVA4+nxIdP1OZD74mBRwrtQ37voxxTmLJJTNkcooxW/F39R8cWpcKkJQX+I2Dj8SBthvPQEB3ba0SGnNCP9xlwfDItEQKpn9uzfyoLTnwpIDQ8E1vw0UhTC3zIp00zyB7TeMu0yMzA2vEOQMDd1MXQNhpvZVTPXTYzwVu4zFm+8zmP0VjbjSi8nCmMHEN1C3kMqS+ypJONk2kUoNvp48ECEnzW4lLRUoC5F92rXTH08GjuGzHi/mfFY8t+L5Vnvt7ra3dSvx2kL8Bj4mMrThOJVtwsMAD8kgujPdAIKc9J4bnV3a7n1tNivPf30dLyszrzL9m7BjrLzCLPU78eoGfWN5Ez68KHImfWqGTe7PJdqAW0x6Y5dTcCXOAMBAys9XpOuYu3xhadWbw3VqZTK5s1na4DoLh8lc3vzWfSjImMGdeDZkxkzHWjZMY=
*/