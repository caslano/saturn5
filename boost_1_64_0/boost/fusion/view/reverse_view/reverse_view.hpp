/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_07202005_0836)
#define FUSION_REVERSE_VIEW_07202005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/view/reverse_view/reverse_view_iterator.hpp>
#include <boost/fusion/view/reverse_view/detail/begin_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/end_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/at_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_at_impl.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_tag;
    struct fusion_sequence_tag;

    template <typename Sequence>
    struct reverse_view : sequence_base<reverse_view<Sequence> >
    {
        typedef reverse_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef Sequence seq_type;
        typedef typename traits::category_of<Sequence>::type category;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef typename result_of::size<Sequence>::type size;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , typename traits::category_of<first_type>::type>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        reverse_view(Sequence& in_seq)
            : seq(in_seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(reverse_view& operator= (reverse_view const&))
    };
}}

#endif



/* reverse_view.hpp
19fywtxT9FCBWanLEbI+tObMRpef/4zGYWpofmn6zMlFOaA1ZbZoVMRAauc0PZg10tLWLViD+sWtrAfF3n7pe4vqm6OHHFppd9yJ3YXBfD00C5M2pF9gvjDbYj20DJd2tU3VFsK8y/SQwMdItwNo/JbroQuz5/4slygObSbLodnT75qIfdC7Uq7N69BWrk00H9owZtaslh+FJa5KPc6pYi60Sszoe+JofrSlGmltK1Z6JSywJvU421o9lGRG3y9Hc6K9Z5YmZ9w7yn1danEdIIh2WBmjG9ALzp8wfxHm9eohSSNt2qKrq4U5t+hhBrOxu54p49AOnNv09M73mzAI5n1Ko1gfSNyO1xXFbkEr9gwQ+wWtp2K3oSvcPf/yLI3DDj1s1Eqbs1HvFO/e9+3Sw++K3YEkqFy31gphtn16uKaRtvvdljzCXAf0cBGknV/XYKc427h9esik9MtdtGzZh68R5jyC608rLef0vBeEJR5X5q5iH2I6LRDmR4tm9vLk4SzC4IQevmc28NbdkcLsaJHMaJ6hOdAqMltR7NhFYR60XcyWtLXXofxO6iGGWZW095eJMfKj5VfsHvSFvScnphMGp/SQj9mLP+9FCrOhDdFIO5htzwRhhjN6MIG0WtUKD6c4tKrM0pdZFivMjZbIzPxjqzgq86weijHr992Q9sIcaDZmTx2dqlCZaFHM6LNINC9aNmYzrh7tT/2CVkcrrciXNvUozq+H3iCtWlLj7sLsF3CfZ1ZuwqZ/hQXRAsweVe1akvK7FNpnczrHZKY+QyvPrHejOJswF5qV2fTN04HaiZaD2c2xGX8TFkBzM8veLscDYZ7LeijO7PqeMh8oDi0rsxO/tv9PGFzRwyxmCb/WH0j7LtpBxQK4Hqfby08nu4r7BLOYHvcaCLNd04OeGf0OOJoDLYoZPY9Ec4bGyeeKaO5Qk88j0byhJp8FoflT1Pf2c+4VwoKhcfL5J5rheqjJ3yTH/FKY/Fwb80Pbxaz84eVLhNlv4P7CTP5GOOaONpPZriolL1B9N0Pj6Pe80RJTGP2eN5o7hdHvh6P50HIwy/O6TQfqlxRxPQPN2gmz3go1+XvlmHsKk79J3hdcaAsVuw8dId+iNFOEOW7roQezdS3aXxcWQOuukfbD10p9hXnv6sESJq1O30U/CHM/0MNlFqdNN95EZT7Swz1mE589mCrM/kQPm0FalVO+SsKsT/WwRSutT0yphZTfn3o4wcrMNOxl1W/WBXx/6en9rQ/ABreX5viPfkvrpR4WK/YQ+sORi5vHC3O8St2swdSsOATRXIo9wradnHklQZj7Ne7JzM5l7WYV5keLY0b3JGi2N3jfIY3dk2CZocbuSbAtaLwtXzeFN6K4typtQWuokVb46/NkYa6/8T5VK231weknhBk+4v0ms645sjqpzE+4XzPTFD68Q5jzix6OMAtmhfOUAxjgE2tLh/w1kikuzAD5gUzeW6B5VMyvYhBugMbMhu4Y2I7qQyvA2vJ85R8dhAUiDOAGaZ/SPwpQW9IYoA6z9/uSf6H60qbeFhvaQ1bfjAu91tP4pTPQufwxmjyXY1x6A0QyozMRml3FHGgJzDbf7T1KmA8tjll8TV0LYdYMqZdpQ2vL7NPF6GLCvGhOZsNn9qtI7cxogHHM6s7psZrmBJpGI61lPv05iosyQCxIm2SaMojmLlpq7XSjVWJG9xZoARWz6VM3l4r50Uoyo/sONIMhdXOomDtVw88+0fyK/QHFof3cV+vo9waNBjpPPIFe7L4DnwWZDFBd6eun4ISYeR11woJmA7xKL+3IwtFGYZ48BvhdJy3D/PqDqC0lDLRnPfv/M90uln3CbCUNsF0=
*/