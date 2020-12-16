#ifndef BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// common_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/archive/detail/basic_oarchive.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {
namespace detail {

// note: referred to as Curiously Recurring Template Patter (CRTP)
template<class Archive>

class BOOST_SYMBOL_VISIBLE common_oarchive :
    public basic_oarchive,
    public interface_oarchive<Archive>
{
    friend class interface_oarchive<Archive>;
    friend class basic_oarchive;
private:
    virtual void vsave(const version_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const object_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_reference_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_id_optional_type t){
        * this->This() << t;
    }
    virtual void vsave(const class_name_type & t){
        * this->This() << t;
    }
    virtual void vsave(const tracking_type t){
        * this->This() << t;
    }
protected:
    // default processing - invoke serialization library
    template<class T>
    void save_override(T & t){
        archive::save(* this->This(), t);
    }
    void save_start(const char * /*name*/){}
    void save_end(const char * /*name*/){}
    common_oarchive(unsigned int flags = 0) :
        basic_oarchive(flags),
        interface_oarchive<Archive>()
    {}
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_DETAIL_COMMON_OARCHIVE_HPP

/* common_oarchive.hpp
9NKM0IzS3KyZqpmumatZpFmpWaNZp3les0GzTbNTs0/zpeaIJoZD5zA46hwbzjSOB8ebE8qJ5azhJHN2cTI4mZxsziFOMaeMU8m5zungdHN6OAOcUY68lroWW4uvNXY/AzMtdy1PLW+tQK1grRCtMK14rXVam7VytQq1SrQqtGq16rQ6tbq1erX6tIa1RrXoXCbXguvEncb14vpx/bmB3GjuOm4yN52bwc3lFnNLuWXcGu55bgu3jdvFfcTt5w5yh7k4bYo2Q1tdm6utqy3UFmvbaHtoe2kHa4dqR2vHaidoJ2unaO/SztbO0c7TLteu0m7V7tDu0u7VfqmN41F4NB6fJ+CJeGY8C54bz5vnw/PjBfPCeUm8VF46L59XxCvhVfPqePW8Zl4br5PXxxvgDfEIOjQdZR1VHYGOVMdJx0XHUydQJ1QnXGeVzjqdBJ1knSydXJ1inTKdSp06nQadyzotOrd02nTadQZ1XuoM62B0SbpMXVVdvq5YV6rrouuh6wU33UnU3a6bppuhm62bo1uoW6JbpXtZt1H3lm6H7kvdIV2CHk2PocfS4+sJ9Cz0JHoOeh56Pnp+eiF6YXqRemv0EvWS9FL1svRy9Ir0SvVq9er1GvSa9dr0+vQG9ZT5qnwLvhXfk+/D9+UH8sP5Efxofjw/gZ/Oz+Jn8/P5xfxSfgW/hl/Hb+J38vv4OH2SPl2fqa+uz9Hn6ov1pfoO+tP0vfX99QP0g/RD9WP1E/Uz9HP0K/Wr9Gv0m/Vv6bfqt+v36r/UxwkIAnkBV8ATOAjcBQGCEEGYIFIQK0gSpAhSBVmCXEG+oFBQLagVNAtaBJ2CR4JewYAAY8A0YBvoGogMvAx8DQINQgzCDSIMog2SDDYbbDXIMMg2qDCoNKgzuGzQZtBp0GPQbzBswBTyhWKhmVAqdBB6CL2EvsIwYYQwUrhGuF2YIcwU5gkPCQuEVcLLwm5hj3BAOCQcEVIMGYbKhjxDkaGFoY2hk+FcQz/DMMN4w0TDFMM0wxzDIsNSw3LDBsNGw1bDDsNOw0eGfYajhiQjthHHSGLkYjTNyNMoyCjEKMpos1G2Ua5RgVGpUZlRndF5o+tG7UYYY5wxyZhurGrMMdY1NjI2M7YytjF2MJ5r7G8cabzKOME42TjNOMM42zjP+JBxiXG5cY1xrfFl4+vG3cY9xgQRRUQTyYv4IoHISeQm8hB5irxFc0WRoljROlGiKEl0SFQoKhXVihpFTaJWUZuoW9QrGhQNiTAmdBOeicDEykRi4mviZ+JvEmoSZbLKZJ1Jsskuk3STPJMCkwqTapPzJg0mTSYtJu0mXSZ9JsMmIyY4MUWsKuaK+WIjsY3YRewm9hAHiIPEoeIIcbQ4QbxLnCnOEReIS8S14vPiZnGruFf8UjwqppiyTJVN2aYCUwtTP9MA02DTcNNI01jTeNM1pttNM01zTPNNi0xLTctN600bTBtNm0wfmfaaDpgOmZLMdM2EZiIzCzMnM3czf7NAs1CzcLNos1VmCWZJZrlmeWZFZhVmNWYNZtfNesz6zUbMMOYMc6a5qrm6uZW5m7mv+VzzYPMw8wjzRPOt5rvMM8yzzQ+ZF5tXmtebXzfvMO83HzWnWChbsC2MLMwsJBZOFt4WIRaRFlEW8RZrLNZZJFpst0i1yLTIssi1KLeosqi2qLVotmiz6LbosyBYkizlLXmWYku4bZWlxNLT0svSx9LPMsgy3DLCcqtlqmWRZbFlhWWl5WXLJstOy0eWLy0xVjgrkpW6lYOVm9U0Ky+rAKsgq1irBKvtVnlWBVaFVvVWzVbtVv1WA1YvrQjWNGuutZm1hbWTtbu1h7WP9VzrQOsQ60jrKOs=
*/