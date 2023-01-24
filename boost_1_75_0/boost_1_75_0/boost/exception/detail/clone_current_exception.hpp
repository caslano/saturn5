//Copyright (c) 2006-2013 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_81522C0EB56511DFAB613DB0DFD72085
#define BOOST_EXCEPTION_81522C0EB56511DFAB613DB0DFD72085

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

#ifdef BOOST_NO_EXCEPTIONS
#    error This header requires exception handling to be enabled.
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        class clone_base;

#ifdef BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR
        int clone_current_exception_non_intrusive( clone_base const * & cloned );
#endif

        namespace
        clone_current_exception_result
            {
            int const success=0;
            int const bad_alloc=1;
            int const bad_exception=2;
            int const not_supported=3;
            }

        inline
        int
        clone_current_exception( clone_base const * & cloned )
            {
#ifdef BOOST_ENABLE_NON_INTRUSIVE_EXCEPTION_PTR
            return clone_current_exception_non_intrusive(cloned);
#else
            return clone_current_exception_result::not_supported;
#endif
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* clone_current_exception.hpp
2zRc88SZjgBZn6pguMYZFwTX6AP7/Fl4AVzT50wAXLNNj2sOcFwDiRYMOghvO9pgnuV6kAmEebYaweYzANp5VEU7NwHa2RYc7cwNXA2DlsmMtujwzo2nO4J3qna2g3fwOnZdX4QHua9P7BXh02vTAh8/ZjY8o7RR1t7R2hbz2D3jcsHfwv2MnrUVaI7L8ZFmLsuxe96ngXaHotdAbndb8eWcoNvlZTloZgIuUJ5cSg6CSe/p5mayWdIKq8itX2tAuMPJ0eDuhQ8I7nx8vT3UJ5Bvs43ztXlAH6mwL9rMw3unAmHge8DN/HwbmxGlmk0HuhClOdCuRXP8BOe5pzqycf61o+0AaNvExQilwIgYPT8bpd/nH8/z0cDHLaOIXa6cjNNJzpNBx2Q83uV2Zet9EijJDLbC43NoAdwzcsQCjNcvL2WsrZLUy+znqgTPF6XLUIvzbD4JU07G6VXtkv0wHk7CP7cL7X4Ne/jSJTLY3oRVh9cWaK6PJNhmv8Fl50lWcjMb/GbUf/wjDjuRj/qPRzC+ADq6/qhzOxHEP2VfldvlW9GusEAZ1fu8V41RnewbozqDwXKnj+I5axybgBaI3ek2mZshTkgFJ59CN9RrHs1qB583js5qgw6WBDeL1N6RXu23t2yPaO/FSzrQ3tH/UHvfdlLb+/I/MC1f2dxP8zA1j28SpwSML0fGiNhEtgG4fXC6Q6miLPoTMkbw
*/