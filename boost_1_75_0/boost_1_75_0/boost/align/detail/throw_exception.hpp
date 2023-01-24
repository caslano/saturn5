/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_THROW_EXCEPTION_HPP
#define BOOST_ALIGN_DETAIL_THROW_EXCEPTION_HPP

#include <boost/config.hpp>
#if defined(BOOST_NO_EXCEPTIONS)
#include <exception>
#endif

namespace boost {

#if defined(BOOST_NO_EXCEPTIONS)
BOOST_NORETURN void throw_exception(const std::exception&);
#endif

namespace alignment {
namespace detail {

#if !defined(BOOST_NO_EXCEPTIONS)
template<class E>
BOOST_NORETURN inline void
throw_exception(const E& error)
{
    throw error;
}
#else
BOOST_NORETURN inline void
throw_exception(const std::exception& error)
{
    boost::throw_exception(error);
}
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* throw_exception.hpp
wr3u+mdKK4a3yRQKGPx8SIFNbMhRvJN/J4qX951Y0FT/xiQZREthZOXHs/HzI1DUABdlByWKTT0G6ZwA3fYcOCvGYj9ASm+3wTW/Hf6cnVY0pl8JXOc6Qy0XW0etNF7+2io/fm4kSyzxNjRyxurCsqBzEtfKj8sH6Yup8AoqUkrlsCS4+pMcrTacI4UGAcX2l9zQA5rioCaPQdRgGfWBbxh8KK6imsr+iExvICOHv0a40pWGs4l5wfikgnyFIVthOwNdpGTi/SvkafefA11g6YD4Jo33dPGizeRqQTxIlq5xvJ+L3llcK75kWw3FCXh1M4c+gB8VjJTiXmbXnSCLH0+mCqiczvkQlKurx+A91rZwh/j6p/y4rI/8uEvnAnapvELfUFwb7yfro3OyPYBsvJ9ct4/6Xia+Kc6TH28AtdmNXTVQtZ3OcxHQCRNreLGQn2PFIg4A6XJ06zUrGH/j073UM2EqhMvkaUshQZMz2Sc/6NSZ9po3Ctia0wAAsVWLzneXSZqki/qnWXXOw3TiofoSrAIH4Gog4P4z2TdfwO1Wy7SavGAhI4ihfTmaaDzX6r50dzqxtf25gTkc+bEASG+GAnnGWIZ6NwEHQfhzNctQ5R57jWCuxudN2ALkxlV5ireNXOgOjgcSWnJoTQAABaj4VR2aM9011z5fyvJZtM8AAAXotAOtbsrUAspF3FWTwWCznP0OCfqPAv7x
*/