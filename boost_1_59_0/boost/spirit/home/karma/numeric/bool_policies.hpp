//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_BOOL_POLICIES_SEP_28_2009_1203PM)
#define BOOST_SPIRIT_KARMA_BOOL_POLICIES_SEP_28_2009_1203PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/char.hpp>
#include <boost/spirit/home/karma/numeric/detail/numeric_utils.hpp>

namespace boost { namespace spirit { namespace karma 
{
    ///////////////////////////////////////////////////////////////////////////
    //
    //  bool_policies, if you need special handling of your boolean output
    //  just overload this policy class and use it as a template
    //  parameter to the karma::bool_generator boolean generator
    //
    //      struct special_bool_policy : karma::bool_policies<>
    //      {
    //          //  we want to spell the names of false as eurt (true backwards)
    //          template <typename CharEncoding, typename Tag
    //            , typename OutputIterator>
    //          static bool generate_false(OutputIterator& sink, bool)
    //          {
    //              return string_inserter<CharEncoding, Tag>::call(sink, "eurt");
    //          }
    //      };
    //
    //      typedef karma::bool_generator<special_bool_policy> backwards_bool;
    //
    //      karma::generate(sink, backwards_bool(), false); // will output: eurt
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T = bool>
    struct bool_policies
    {
        ///////////////////////////////////////////////////////////////////////
        // Expose the data type the generator is targeted at
        ///////////////////////////////////////////////////////////////////////
        typedef T value_type;

        ///////////////////////////////////////////////////////////////////////
        //  By default the policy doesn't require any special iterator 
        //  functionality. The boolean generator exposes its properties
        //  from here, so this needs to be updated in case other properties
        //  need to be implemented.
        ///////////////////////////////////////////////////////////////////////
        typedef mpl::int_<generator_properties::no_properties> properties;

        ///////////////////////////////////////////////////////////////////////
        //  This is the main function used to generate the output for a 
        //  boolean. It is called by the boolean generator in order 
        //  to perform the conversion. In theory all of the work can be 
        //  implemented here, but it is the easiest to use existing 
        //  functionality provided by the type specified by the template 
        //  parameter `Inserter`. 
        //
        //      sink: the output iterator to use for generation
        //      n:    the floating point number to convert 
        //      p:    the instance of the policy type used to instantiate this 
        //            floating point generator.
        ///////////////////////////////////////////////////////////////////////
        template <typename Inserter, typename OutputIterator, typename Policies>
        static bool
        call (OutputIterator& sink, T n, Policies const& p)
        {
            return Inserter::call_n(sink, n, p);
        }

        ///////////////////////////////////////////////////////////////////////
        //  Print the textual representations of a true boolean value
        //
        //      sink       The output iterator to use for generation
        //      b          The boolean value to convert. 
        //
        //  The CharEncoding and Tag template parameters are either of the type 
        //  unused_type or describes the character class and conversion to be 
        //  applied to any output possibly influenced by either the lower[...] 
        //  or upper[...] directives.
        //
        ///////////////////////////////////////////////////////////////////////
        template <typename CharEncoding, typename Tag, typename OutputIterator>
        static bool generate_true(OutputIterator& sink, T)
        {
            return string_inserter<CharEncoding, Tag>::call(sink, "true");
        }

        ///////////////////////////////////////////////////////////////////////
        //  Print the textual representations of a false boolean value
        //
        //      sink       The output iterator to use for generation
        //      b          The boolean value to convert. 
        //
        //  The CharEncoding and Tag template parameters are either of the type 
        //  unused_type or describes the character class and conversion to be 
        //  applied to any output possibly influenced by either the lower[...] 
        //  or upper[...] directives.
        //
        ///////////////////////////////////////////////////////////////////////
        template <typename CharEncoding, typename Tag, typename OutputIterator>
        static bool generate_false(OutputIterator& sink, T)
        {
            return string_inserter<CharEncoding, Tag>::call(sink, "false");
        }
    };

}}}

#endif

/* bool_policies.hpp
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
*/