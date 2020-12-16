///////////////////////////////////////////////////////////////////////////////
// tail_variate.hpp
//
//  Copyright 2005 Eric Niebler, Michael Gauckler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005
#define BOOST_STAT_STATISTICS_TAIL_VARIATE_HPP_EAN_28_10_2005

#include <boost/range.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/serialization/vector.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // tail_variate_impl
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef
            typename detail::tail_range<
                typename std::vector<VariateType>::const_iterator
              , std::vector<std::size_t>::iterator
            >::type
        result_type;

        template<typename Args>
        tail_variate_impl(Args const &args)
          : variates(args[tag::tail<LeftRight>::cache_size], args[parameter::keyword<VariateTag>::get() | VariateType()])
        {
        }

        template<typename Args>
        void assign(Args const &args, std::size_t index)
        {
            this->variates[index] = args[parameter::keyword<VariateTag>::get()];
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            // getting the order result causes the indices vector to be sorted.
            extractor<tag::tail<LeftRight> > const some_tail = {};
            return this->do_result(some_tail(args));
        }

    private:
        template<typename TailRng>
        result_type do_result(TailRng const &rng) const
        {
            return detail::make_tail_range(
                this->variates.begin()
              , rng.end().base().base()   // the index iterator
              , rng.begin().base().base() // (begin and end reversed because these are reverse iterators)
            );
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & variates;
        }

    private:
        std::vector<VariateType> variates;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::tail_variate<>
//
namespace tag
{
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct tail_variate
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::tail_variate_impl<VariateType, VariateTag, LeftRight> > impl;
    };

    struct abstract_tail_variate
      : depends_on<>
    {
    };

    template<typename LeftRight>
    struct tail_weights
      : depends_on<tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::tail_variate_impl<mpl::_2, tag::weight, LeftRight> impl;
    };

    struct abstract_tail_weights
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_variate
// extract::tail_weights
//
namespace extract
{
    extractor<tag::abstract_tail_variate> const tail_variate = {};
    extractor<tag::abstract_tail_weights> const tail_weights = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_variate)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_weights)
}

using extract::tail_variate;
using extract::tail_weights;

template<typename VariateType, typename VariateTag, typename LeftRight>
struct feature_of<tag::tail_variate<VariateType, VariateTag, LeftRight> >
  : feature_of<tag::abstract_tail_variate>
{
};

template<typename LeftRight>
struct feature_of<tag::tail_weights<LeftRight> >
{
    typedef tag::abstract_tail_weights type;
};

}} // namespace boost::accumulators

#endif

/* tail_variate.hpp
LVlnffqknqm/cWvj/pJ04yCtsxJknRVZAfNCa0LYq5u63h9RfY0hDiFKTplWvbGaeq7HgxHHBynz149zSWfs9ziH27D497gOexzdDnPXZJ/Uq56/H6sV44FeyWelacztPCyrnWbU++owKusvsxjr3A7PpsA0ludIw0CqHvdSUtRi/WPH+qc/Hvkm33ZpjXPbYCbLohiFTFqoc6BHY3xbqtWv0SxfBlpo4LWMbmlIjqXVjDLn6MYgjPZYHnEK1egBWReFAFNVfMFs0NNHEExJhTJtDqbHtARNgiW8KnMdHNfLx0KtrK5wR8cPzpIMjH8kx3qi2xpezTzzhBDzVqbVaRzVecJj3e+zHnXuRx1qcTvAf3FfAARqS1pjytXtOk75oHBor47r2vDoyNIZviGjgxL4XRhcduJqOS3aJRs/OLo6sQrq5M0+gURAOvpC3f0T8G49FBhicx4C7hmbwO24RD6FojFT8hRmeShMsOA4IgQO1LxwFxOCuj/nIL3LRQ8Pt+OAT6kjEmUiooCa5MCrEBFP8OXpKxK9x12RIVO6DoNm46b/3g/rk3l/grYBEnvr0aedifd9TEurXwb7FLmx0jF2w/+8+no8oXQLmLFq/FZkbO3DtijvrvrZLWo6wsGKOhI2R96Kya1uJqLOxXoyNnEBRNZpEw++QyLrhtCXGUbXRHegX0Lyp/iNV4exj0VBcPtAGxIsIsrRjFYPi1E1kH6R2z/OHjOunocPEUJf6Da2q9dgRoXZbZXoxzCLjaLlXIHMl6nhroSTd+MSt7OfLf/T8dtKl7mNG23udtUdk8YgHtGaTZpHF9m439TCeCiHr+TvASKQSF0HoKhLnf2RybiOA036w94gsFXENGgkW3eo5IDm53GWm2zOnSjz09J4yuHLP5Gqb1SaLj93EloUH5PbnpqeEezVOtNY6y6+kRfq+Oehq1ZCCe8O3Jhg7MQYmnEDhNeSOviBXrYm/jyRex98Sa1LFC8k+yWUfI+HSL0f6U8y7iagDQgjoXfUS9xa8MksVKhk+ckQwBsTjW0IpDNMavhYBL/EwZuUAkA8tefDLHUlMhv9A7/slUimCZ8NpC6g0Fwq1qKnmasok2yEQD6uNj8upj2+I/D14/sa6GAQvv3xfRhfN8JiLHb5QEaOtf82n2qm5+oV3tXY9L/xKSf/PWKSr5svzqrLMmfnkRCUN90Zka+bqAdmSd+GJeouIlE3oYgZr1WUqIMGJq8wA/cGsMQytuGvJeRYvYGkao8xidtJo3+BuB29/+nhn5G300afSt7GHH0PRtDibHYGUa3rCHhxBh64YvunhUXtvqPDTyP/fC5C96nsHx42yd+7Xjkj+bvmXaeVvy/PFfnbvN8M/ZRZrH54dljrkKm11R+rS/7M4jQP4Oe1QXcW2kwo7KOmQcEAcXKYoDGnqXsxGFDEbZHPWENTBmK7g91jebe3lXQwcJb2gLBvcBmwbsQDKWz38eT/+xnEv9lm/griqY2j2VqqyLa0mqA9ss6Wc41g7oOiUurZ9UeV+/M9Iz6Efz9LdlFDvAI5wOT1oWPSC6QQpCXCExpRqdQer/pkFG8K05n8hph6aA5Eq+oTxhI8dMHI34gltvGT5oVvd32QtScurAKuAwfGe2LJmYMZK82DWQ6+nutWGWJUChotljvaP3DfVXwClLk5xV2HuPT/8BBWT2xAOlPsX0FDCPyUN/Xt/JCs0NCgMH7CN4ykcJ1NR7XVkpFcPcyg6shfiN735PQk5GTRrC3I+eIZjgIMJs1k5FwI5DQMv9+sWt/H6vRq/nWh0gsj7d7aR9r95OCoWgYFci3O0TK4ivvfHpSmyv1vP4ygIu2uW+1jy9vuyhU=
*/