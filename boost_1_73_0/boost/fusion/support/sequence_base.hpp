/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_BASE_04182005_0737)
#define FUSION_SEQUENCE_BASE_04182005_0737

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end_fwd.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        struct from_sequence_convertible_type
        {};
    }

    template <typename Sequence>
    struct sequence_base
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence const&
        derived() const BOOST_NOEXCEPT
        {
            return static_cast<Sequence const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence&
        derived() BOOST_NOEXCEPT
        {
            return static_cast<Sequence&>(*this);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        operator detail::from_sequence_convertible_type() const BOOST_NOEXCEPT
        {
            return detail::from_sequence_convertible_type();
        }
    };

    struct fusion_sequence_tag;
}}

namespace boost { namespace mpl
{
    // Deliberately break mpl::begin, so it doesn't lie that a Fusion sequence
    // is not an MPL sequence by returning mpl::void_.
    // In other words: Fusion Sequences are always MPL Sequences, but they can
    // be incompletely defined.
    template<> struct begin_impl< boost::fusion::fusion_sequence_tag >;
}}

#endif

/* sequence_base.hpp
SybQfbRm34nGjpv5eLS7Jd2UYUzrUkw96m8tejwRJR73uN2xsE+pb+ukvsfbWK831VQROw2tqUyqs6bqREO6O6V9gxbuJURPv02PX3Gp0WjAF3cplltSubU8WFPVgruJx0zL0TRajDXUWauOaz1hbygQCKlKTZnb11VzreIIidyMVc4VUXyqU/XGfFGlZr/xP5fXH4zVVKn1rkjQXVMV9h7iW/mfZje6ZM1l0xVWgv5o1B/2
*/