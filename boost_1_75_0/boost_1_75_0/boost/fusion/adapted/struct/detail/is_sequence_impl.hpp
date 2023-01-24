/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };

    template <>
    struct is_sequence_impl<assoc_struct_tag>
      : is_sequence_impl<struct_tag>
    {};
}}}

#endif

/* is_sequence_impl.hpp
0c+zTJiidu+bMEX/vEDYfzkICoJxUB9QNFiOhf2Xk5b8RJZekhrK2H9O9DOVJxnpSrYXh+9GRgCExSzsJsSHEgRgVoYMV/UNzrYiZSEM9UwJeQFnMFqgR2a+kS6u8+fqmnM5urju5jJ5ChbfgVTG4kNMlSe7mj6HUQoYn3OiPwTcWq8Wf5Bb62Rwa72EUHm8uOBOo7DfPBPHjt8tZ3jCZIWnDhZP/UKoOWiR3MyCY3ZcF8hZD9VZKyYjIKRW8pdg8geef+QGTKDP4wFGkV5hrMJUhZ9J75v8rLVRG6loiW/fWLeNcs02yg3k4QKTB8hhRzCGuVghFs5IEX2UH09OGEUrdiH2oHVk5TFgQ7U2FXxtOwQ9SzbEOkkDp9bk2k7gm9s+qECq4W8FBTicuxHXXUZTAlouvXjOGb9fgSysefUM+aWWq61tRUsjpB0028A5KjqAhWaoONxJSednBLAh08xYcTjWHsYHo2kPo7q+PQx0Qd2+QjqerltB210rVqCb6WZjxFr+Y4j84/a16G/nXQX5iAYqp2u+MQkzhdXABLSd8yr0zp65wibcGs/WIz2J4M1cAG/WdZZ6snvddAUz9BqyG6FutBvFt6DdeLulxAz9aIaJGVr9ron6tvQ5sBsT5kvfpoHz2fPJF216zedleAtEgY7r3m6P/pPgRZ+f45bQZukmiOGkHwj1Iaf2BtyJPDyzLojhkmICjLgm
*/