//  Boost string_algo library string_funct.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CASE_CONV_DETAIL_HPP
#define BOOST_STRING_CASE_CONV_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <locale>
#include <functional>

#include <boost/type_traits/make_unsigned.hpp>

namespace boost {
    namespace algorithm {
        namespace detail {

//  case conversion functors -----------------------------------------------//

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

            // a tolower functor
            template<typename CharT>
            struct to_lowerF
            {
                typedef CharT argument_type;
                typedef CharT result_type;
                // Constructor
                to_lowerF( const std::locale& Loc ) : m_Loc( &Loc ) {}

                // Operation
                CharT operator ()( CharT Ch ) const
                {
                    #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                        return std::tolower( static_cast<typename boost::make_unsigned <CharT>::type> ( Ch ));
                    #else
                        return std::tolower<CharT>( Ch, *m_Loc );
                    #endif
                }
            private:
                const std::locale* m_Loc;
            };

            // a toupper functor
            template<typename CharT>
            struct to_upperF
            {
                typedef CharT argument_type;
                typedef CharT result_type;
                // Constructor
                to_upperF( const std::locale& Loc ) : m_Loc( &Loc ) {}

                // Operation
                CharT operator ()( CharT Ch ) const
                {
                    #if defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (__BORLANDC__ <= 0x564) && !defined(_USE_OLD_RW_STL)
                        return std::toupper( static_cast<typename boost::make_unsigned <CharT>::type> ( Ch ));
                    #else
                        return std::toupper<CharT>( Ch, *m_Loc );
                    #endif
                }
            private:
                const std::locale* m_Loc;
            };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

// algorithm implementation -------------------------------------------------------------------------

            // Transform a range
            template<typename OutputIteratorT, typename RangeT, typename FunctorT>
            OutputIteratorT transform_range_copy(
                OutputIteratorT Output,
                const RangeT& Input,
                FunctorT Functor)
            {
                return std::transform( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    Output,
                    Functor);
            }

            // Transform a range (in-place)
            template<typename RangeT, typename FunctorT>
            void transform_range(
                const RangeT& Input,
                FunctorT Functor)
            {
                std::transform( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    ::boost::begin(Input),
                    Functor);
            }

            template<typename SequenceT, typename RangeT, typename FunctorT>
            inline SequenceT transform_range_copy( 
                const RangeT& Input, 
                FunctorT Functor)
            {
                return SequenceT(
                    ::boost::make_transform_iterator(
                        ::boost::begin(Input),
                        Functor),
                    ::boost::make_transform_iterator(
                        ::boost::end(Input), 
                        Functor));
            }

        } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_CASE_CONV_DETAIL_HPP

/* case_conv.hpp
E+c/qMqyWERo/LVOEaqZW9HYRkNnJOp+k707zGHjiKa7VCaNUFlcZnrUrqFj7FSXSao/Raqx86mG0s3fIc2Wv/Ch6MkuuNyBcKYT5AEj3zRuU7pGpdO7o7XAvHU6JTma9Y1HIyLNjPPwudL8Nq7+tq5o/x4nlsM3spjFexO2H69hAPB29pAx1VNBJ0nDtDMdOX2DcnqCcupn07pBaH11cWcNOM22MKjdwbHgXGmwMwn/XcG/LQnfYb5K+PVcLeWukDHRFWgod6Wp+JjwYL/oya0anOPTvKR/mvgm9SCy0UBpUjrQ7UXALnqWFZ3rqGD99XnZHmpuuqZbY7iP1eTYmEzzYUH8FtVmfwrBLAjIgjC3Q9DN6wRrADaeW1g9GAt9107UvJixRNkd+Qlvple3hqOliNFOvFWuiV+qhpPJFoN8tT7HvsqfOj+tvGtuuZt7IA8pxl5r577Z5wdtCep1EWn+axxJvQ/90wyg4kiX/WYgBmjSWB8bnUkqAFUzVfD2p3mod2MUVo6oRtFBX6x/XBPe5ag6OXZuhjnaoLqVvJI0wd2VShNMiRne5ax6nhUMcI7kCW7JQfbSqlbG1z0t49S3kAKhD05GdzF6RxJ6SKGXKPTyZPTcLqkfCXTDJO+H26i2ln8HJVDdkPVlWt+hfvwQ1E/xGyCBGJ5GusxdKnROGp5bZlxufkDcFR3hkXu/KMWdVSxfOOA2FbkcIzEluvwGmdoTf658CMr2VfOoc5v5t1CckR5LdXHyPHUqvIvPGiMKjTjf5SniDy8Rv86nzruH4i6Lor1tQdpkNYdSjSYjEYs1MNZJCoewCJQo5gU/xQe1k1FPLfVvc5j7AH7J+vf6O6zxiMyLDgq690luW2JMsmtwJwBfiAbQeiWAUKpOt9TegLAM+gNXUoraa/4hWe1VWjrtF6Oe0JN6QijC5kpi/9b+4V2ZVW9QRZ/nsPXeBaKglgIvSTtlf4tN5qKrpA3kKNAXV+wPoH5e/ZVVP+aNT3xGvSy/AkChK9t8JCKDchcrK09sqo4MGYjPHX8VTEQ3ZKfghKhSvctoDo6GIK/x0PwDmZV/OShbbIr8K2f5dzuXiKwtWwlyjZn9B1ZBfLHz8qhkkyEoLFEQXkSDAbCKjd3mYU+KyOiDUqkZj8uWghdminwhXEQxP3xCkNvSBHmiPi8rCRnnHYss1Lig3kxXXBvAhF/PKg9PV8wy9Pwoglq/Ge7YW3WyBB6KwJdo/grBVLbaLARLarV4J0RzMeR4ovHJrCpnIoTP38IQolhpIupxYkHlUeYPbqPOPcxDgReCHSeSjHlT7ErDSO5MZkEjXsNPEdEWO89lDnJwSLE56IciXWgkINQeJG1sE9InFDQVah2fYjMYZxzrxuUkJVAG1HkvwDkYrQrA1yo+ku3d639pzb/Z5L3IvA+Vi6OAlSXmsCupmrJI48tJuS1gOdXXX3+mBqvPN3Dz/LnLIcYfSs7eBPPh6XyScRFf4m6sNw8RKuTCyF8phWnv9UJakfnkFXarjsMci+gpBT3mGVfaDTOQWuGqi0Xmn2ZOoxjRTPo4fh7poGZzmERKCIgk/fOV4L96Elu2+MLK1owAwc0JaG5K7WUS+aefRW71jQYUW51D/NKPIFrnTYfFLNmDSUzylQjZZvnNltmuxfRfYZvtGKFlDCrvQOzZ79wq6Yvv5B5sYm5xIJByeDtsKesekumP881C95Fd/Wy68YMD/8CBv6HA48mY+FSYJ1WD75NJ1Uc/E9v3sYT7LOPeI7b/M6ph+P4d3lmzNn98DVm/v4iJ+0DOYztvVQxGR7GjZ5AI/8nITgvnydfLjIP7eLJJ9N2bOk2iLT/rjJDGETqC0bM=
*/