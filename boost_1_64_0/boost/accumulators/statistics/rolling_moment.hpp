///////////////////////////////////////////////////////////////////////////////
// rolling_moment.hpp
// Copyright 2005 Eric Niebler.
// Copyright (C) 2014 Pieter Bastiaan Ober (Integricom).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_MOMENT_HPP_EAN_27_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_MOMENT_HPP_EAN_27_11_2005

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>

namespace boost { namespace accumulators
{
namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // rolling_moment_impl
    template<typename N, typename Sample>
    struct rolling_moment_impl
      : accumulator_base
    {
        BOOST_MPL_ASSERT_RELATION(N::value, >, 0);
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t,void,void>::result_type result_type;

        template<typename Args>
        rolling_moment_impl(Args const &args)
          : sum_(args[sample | Sample()])
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            if(is_rolling_window_plus1_full(args))
            {
                this->sum_ -= numeric::pow(rolling_window_plus1(args).front(), N());
            }
            this->sum_ += numeric::pow(args[sample], N());
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(this->sum_, rolling_count(args));
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum_;
        }

    private:
        result_type sum_;
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_moment
//
namespace tag
{
    template<int N>
    struct rolling_moment
      : depends_on< rolling_window_plus1, rolling_count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_moment_impl<mpl::int_<N>, mpl::_1> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_moment
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, rolling_moment, (int))
}

using extract::rolling_moment;

// There is no weighted_rolling_moment (yet)...
//
//// So that rolling_moment<N> can be automatically substituted with
//// weighted_rolling_moment<N> when the weight parameter is non-void
//template<int N>
//struct as_weighted_feature<tag::rolling_moment<N> >
//{
//    typedef tag::weighted_rolling_moment<N> type;
//};
//
//template<int N>
//struct feature_of<tag::weighted_rolling_moment<N> >
//  : feature_of<tag::rolling_moment<N> >
//{
//};
}} // namespace boost::accumulators

#endif

/* rolling_moment.hpp
3s25JyNzEtzeOaxoRO0RnHY3wxnhDZH10Fgk81OPsHXZnGau3JMNPI0gyBTHvJlMBr16lTyE0xLSouxz7+G93pOi7raTXHhvSQQWusEIVLq3XwRdpXfMICx+yvpeafZ3bUBgw9pp7VcSBldgNSntTQ+3fcvTc1fGl37MZZul594ByGJgXbgemS1dsSc81VujsYBHkAxhuXwekXUYPw3K0wp30H+1kQuGdC9NoAXeemwZJNkV4Yl2pWzJrmsiFyG47EVetG6ft4Q161eWoVM17fc/glD6mDUZ+TFrD5ZBR+uxB043iAxJD9vs20uudQyIcrvXDoHvMEyafrmzakfgdyF+A9DaAmi65IO6Wu2IJNi0xvnSpMyVoMxumjLL5R7gzagdAehdIOT6C4JSMk5rNSbVpbNPfpZNlFkWQPvP0hxfSLVAm89IBU8GaxD7jos7xoYk2ez33o7R5vHh7Pbc8QibbZYGhdFBt1btBFDYNeAKnEb5oeXKl/RlZ29R73WIDTEKdOECRv7W5fIzp0qH+58VuzHsaRFx/nGfE8J81bwHu57DDwirut8GFvuGwXNV84t5yyKF0ZarfmTIMozjzfh+Cn+78HcFwq/hb+1/6ae6/JDvXyrZ9H50ufAUslGm0sTKR3e+CD5kuu5uI667p5awz2piMryGd+TlcCxN177EOvLvS8IQ5x7HXGsbyof5MQfKfO6F3vn3hMRFhrjD1vj2JO6kC7+2XrI9mFTLE+Onz+za3JOkxjmHqCMQIrjtqafcUC0nH09hdI9GNjRUXayZVEdrV8HlInjpGiYS7btCkZIC6VSfOD4PlHxK6Sk73XnX6YgC4iI75x5EKO+6eFlAX+A4qrGVAZXj7AAloM0VoQQQbQjUzAwToDQB6IVQAeigzQAoQdpPMgHSEYRZWN6eFpU3pbOAE2OThbofI/chijqAf/pWY3MYwodDzEJuKbRbr+6D/YXeETm+PKhB/7zFSS08caKfO+eUQTrLfUWzk0JyfrAXHmmRe8p221hXwSjpw26b9KGtzbx0lblp01oDw4CJLHqh92CMKG0uJs+gBeOk+LM2EeNc1/8oIl1oz/AZXdqcfo0QSM0pP4XD02TKj6Up/1dzyrdvaSoUBD9mvB4TGdKxUWSIC38f4u8I/uJiI0P2Nfrv4AHE92/RZ3B7Fy3OhYTtC/VEulg6A8Y7hRBF5lOeEoklOm3MsQ+y9FtisxDrjUD4YFsamgUidvvJF83j9WdkqopIuwI/Kqpc/yWR4fXGvNk6Fi3swDEibx7rZkAKdpHPJzpfsi83db7y+9VR4wCJ93jucV9OR/baR2mbhT7SAGy+uw3LDqNbBGibRK39CDLzp+NQPjwZrc5djrgCxNndxXnhbRCjLkxGYkwz/KROb4u3uGtt5M7XL1VzarD1mWfdXiT9lvqRwfDlGFrgIG7S6VIZX2yYxF1jDhwVtjB0fnIaoK8QxiXY2LwLlYA4PndmXEhOO3wlhHi+hsWjwlAx706yFCeP+uAERKtjHVjDIY41nZexGpdaUpOvq7oUvqtx/Cc5Q+w+E63l/+vVaxegHMon9AWuUUMKpBL04Bv1Oin+RJjYECQAkxBBeWY61AkoNKKmJ1ATypgNvE6qFANRc98JKgs1o7JYVEY3/jmjUCXVoF6SKnnDHg1VqLAQ38Ye9JXd3WwAfxHqMTTCVaMJ8huHxqiRT6QRJpHSZtzI24iyOyCNxZnM7hgAhQqb3dEn3l4v3YFgZ3s9VzzCToQ7I5yFsBPh0Qgj+4N0kEDUaERNxfdUu+O+BRyVRynI8AyHeC+OtCWSpiMppNpcQOgAKbEgmKjMSbAkKWdveS3Ss6UMFWXqjAg=
*/