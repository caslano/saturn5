///////////////////////////////////////////////////////////////////////////////
// droppable_accumulator.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_DROPPABLE_ACCUMULATOR_HPP_EAN_13_12_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_DROPPABLE_ACCUMULATOR_HPP_EAN_13_12_2005

#include <new>
#include <boost/assert.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/accumulators/framework/depends_on.hpp> // for feature_of
#include <boost/accumulators/framework/parameters/accumulator.hpp> // for accumulator

namespace boost { namespace accumulators
{

    template<typename Accumulator>
    struct droppable_accumulator;

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////////////
        // add_ref_visitor
        //   a fusion function object for add_ref'ing accumulators
        template<typename Args>
        struct add_ref_visitor
        {
            explicit add_ref_visitor(Args const &args)
              : args_(args)
            {
            }

            template<typename Accumulator>
            void operator ()(Accumulator &acc) const
            {
                typedef typename Accumulator::feature_tag::dependencies dependencies;

                acc.add_ref(this->args_);

                // Also add_ref accumulators that this feature depends on
                this->args_[accumulator].template
                    visit_if<detail::contains_feature_of_<dependencies> >(
                        *this
                );
            }

        private:
            add_ref_visitor &operator =(add_ref_visitor const &);
            Args const &args_;
        };

        template<typename Args>
        add_ref_visitor<Args> make_add_ref_visitor(Args const &args)
        {
            return add_ref_visitor<Args>(args);
        }

        ///////////////////////////////////////////////////////////////////////////////
        // drop_visitor
        //   a fusion function object for dropping accumulators
        template<typename Args>
        struct drop_visitor
        {
            explicit drop_visitor(Args const &args)
              : args_(args)
            {
            }

            template<typename Accumulator>
            void operator ()(Accumulator &acc) const
            {
                if(typename Accumulator::is_droppable())
                {
                    typedef typename Accumulator::feature_tag::dependencies dependencies;

                    acc.drop(this->args_);
                    // Also drop accumulators that this feature depends on
                    this->args_[accumulator].template
                        visit_if<detail::contains_feature_of_<dependencies> >(
                            *this
                    );
                }
            }

        private:
            drop_visitor &operator =(drop_visitor const &);
            Args const &args_;
        };

        template<typename Args>
        drop_visitor<Args> make_drop_visitor(Args const &args)
        {
            return drop_visitor<Args>(args);
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // droppable_accumulator_base
    template<typename Accumulator>
    struct droppable_accumulator_base
      : Accumulator
    {
        typedef droppable_accumulator_base base;
        typedef mpl::true_ is_droppable;
        typedef typename Accumulator::result_type result_type;

        template<typename Args>
        droppable_accumulator_base(Args const &args)
          : Accumulator(args)
          , ref_count_(0)
        {
        }

        droppable_accumulator_base(droppable_accumulator_base const &that)
          : Accumulator(*static_cast<Accumulator const *>(&that))
          , ref_count_(that.ref_count_)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            if(!this->is_dropped())
            {
                this->Accumulator::operator ()(args);
            }
        }

        template<typename Args>
        void add_ref(Args const &)
        {
            ++this->ref_count_;
        }

        template<typename Args>
        void drop(Args const &args)
        {
            BOOST_ASSERT(0 < this->ref_count_);
            if(1 == this->ref_count_)
            {
                static_cast<droppable_accumulator<Accumulator> *>(this)->on_drop(args);
            }
            --this->ref_count_;
        }

        bool is_dropped() const
        {
            return 0 == this->ref_count_;
        }

    private:
        int ref_count_;
    };

    //////////////////////////////////////////////////////////////////////////
    // droppable_accumulator
    //   this can be specialized for any type that needs special handling
    template<typename Accumulator>
    struct droppable_accumulator
      : droppable_accumulator_base<Accumulator>
    {
        template<typename Args>
        droppable_accumulator(Args const &args)
          : droppable_accumulator::base(args)
        {
        }

        droppable_accumulator(droppable_accumulator const &that)
          : droppable_accumulator::base(*static_cast<typename droppable_accumulator::base const *>(&that))
        {
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // with_cached_result
    template<typename Accumulator>
    struct with_cached_result
      : Accumulator
    {
        typedef typename Accumulator::result_type result_type;

        template<typename Args>
        with_cached_result(Args const &args)
          : Accumulator(args)
          , cache()
        {
        }

        with_cached_result(with_cached_result const &that)
          : Accumulator(*static_cast<Accumulator const *>(&that))
          , cache()
        {
            if(that.has_result())
            {
                this->set(that.get());
            }
        }

        ~with_cached_result()
        {
            // Since this is a base class of droppable_accumulator_base,
            // this destructor is called before any of droppable_accumulator_base's
            // members get cleaned up, including is_dropped, so the following
            // call to has_result() is valid.
            if(this->has_result())
            {
                this->get().~result_type();
            }
        }

        template<typename Args>
        void on_drop(Args const &args)
        {
            // cache the result at the point this calculation was dropped
            BOOST_ASSERT(!this->has_result());
            this->set(this->Accumulator::result(args));
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return this->has_result() ? this->get() : this->Accumulator::result(args);
        }

    private:
        with_cached_result &operator =(with_cached_result const &);

        void set(result_type const &r)
        {
            ::new(this->cache.address()) result_type(r);
        }

        result_type const &get() const
        {
            return *static_cast<result_type const *>(this->cache.address());
        }

        bool has_result() const
        {
            typedef with_cached_result<Accumulator> this_type;
            typedef droppable_accumulator_base<this_type> derived_type;
            return static_cast<derived_type const *>(this)->is_dropped();
        }

        aligned_storage<sizeof(result_type)> cache;
    };

    namespace tag
    {
        template<typename Feature>
        struct as_droppable
        {
            typedef droppable<Feature> type;
        };

        template<typename Feature>
        struct as_droppable<droppable<Feature> >
        {
            typedef droppable<Feature> type;
        };

        //////////////////////////////////////////////////////////////////////////
        // droppable
        template<typename Feature>
        struct droppable
          : as_feature<Feature>::type
        {
            typedef typename as_feature<Feature>::type feature_type;
            typedef typename feature_type::dependencies tmp_dependencies_;

            typedef
                typename mpl::transform<
                    typename feature_type::dependencies
                  , as_droppable<mpl::_1>
                >::type
            dependencies;

            struct impl
            {
                template<typename Sample, typename Weight>
                struct apply
                {
                    typedef
                        droppable_accumulator<
                            typename mpl::apply2<typename feature_type::impl, Sample, Weight>::type
                        >
                    type;
                };
            };
        };
    }

    // make droppable<tag::feature(modifier)> work
    template<typename Feature>
    struct as_feature<tag::droppable<Feature> >
    {
        typedef tag::droppable<typename as_feature<Feature>::type> type;
    };

    // make droppable<tag::mean> work with non-void weights (should become
    // droppable<tag::weighted_mean>
    template<typename Feature>
    struct as_weighted_feature<tag::droppable<Feature> >
    {
        typedef tag::droppable<typename as_weighted_feature<Feature>::type> type;
    };

    // for the purposes of feature-based dependency resolution,
    // droppable<Foo> provides the same feature as Foo
    template<typename Feature>
    struct feature_of<tag::droppable<Feature> >
      : feature_of<Feature>
    {
    };

    // Note: Usually, the extractor is pulled into the accumulators namespace with
    // a using directive, not the tag. But the droppable<> feature doesn't have an
    // extractor, so we can put the droppable tag in the accumulators namespace
    // without fear of a name conflict.
    using tag::droppable;

}} // namespace boost::accumulators

#endif

/* droppable_accumulator.hpp
QpNFDZ7D+LJPJn3Eq0/Taz6m1QmPCE7DSXx7DtzbxX3HLJbmH5rFOy4WqNhWJUTKhg4UgrmGxDpWL57pirjxvyeSWbwqbzNKMH8BLHarcVK3l7cIWu1FDtYZPPeBm4/j3CcISo6hqoieT9Nqx0ug36lAbx+PrFQNMFDgWpdi/wn6MO7kGicthZeVu8/RbOZ4ok9au8vyNE/3SRX4rRPORS5QR0wCVdUpU6e55Lx+ebWc7o0/lX9Rb2ZYfSI4g8ENZ3eYUyTiZn4s1SaCsp03y8mUrawsBIVFYc7x3Z6UozS9HKbK1sh+uMaCSZ7JlJ9QDyl+SCq3v7WhFZths88agdSoNCuvoHp9klPCDE8M6CRC5Fwup5V+SmtuT3jS5Fq4hddHG7f3ErWsju/JB7+beQqPPZQhC4gu+IbvqBX7DARqW6n8/ObgUxLl5ezN/qDAvJj7qRYXiZ5esb+XlUyTJDg/KGY0meETJNUXj6BNSgsl0opwNj4e9typ8jmvo2xJo2HjEYeb18YjuENU99dkET4nINr+RaAnib9LGNeLwHxJ/a4W7ClTlWxIYWN3chCtJL6gnw5+fMKP7twK0g3HarScLOcgvhZUY1UdBXK2mstqqSkkMNQLi3ovYsBLFH1R2Bt3mI+dqGSod3sgNZKGwIXVW1mCpcB+lIGXP819W70ISp9OZKkFj5Kt6sFldC/Zw0LsHgYCEkvtyHvuNEBTLoiVLQfw0CxzdlA1O99CaIsiZtKQi/RN2Jyvf0x1IQEPZGHZnCIVMhLRbLLTfFaRh6jUfs2nusM/SZNNcKhqkx5vRePsfQ9YQyLfk7Scg2YWyfhWlQAB3YGC4XY7FvjCOMvKZNTFcnXhyzGNUBfdx/nTSHI+HpyWxTJO0ve+dOuiNLxujVwAL0OvAszbyTEYfsdqXGgB7QZH63IloqrNG69SshEyh0w51mrGMDrhgBNU43wdngHSoj7PWNjHSZQS7uwrMOI5OAm++78lXrkZiut4i+Z8TSv51H2zzkL1Kg6NSPcqi6CHzpcY7zplCtvO9BeoXkaUq+y3OG3J9Tny+LHKZQ3HgXkVX6G5UL1Fx8T5bDhO3G1l7hrRq/iU/EYVdx6CmcWwekuEqaNkPlZS+qWczHMol/28FHJ+RfmWqJx1Ir6LSYb7CoTtUzAVcWhL3m6B7kkJ2qM58kLdvXR/eqKrQOCOZSzlUVxiupfv4L2EPZW7l96HsAZWFSWEy1LWtk9JyLYIPlrNVT9LDt72sQifc4kXcMYTPIvPL5oFqijXIwLr0MEPzXDUv0Bftl69ezwFXX2Z9CGjvt50LVuel45vlsRBd+DbnH+upHU6p7XCmos5jBk4TTz7patYtO69404TTDZzsPJ+32F7r6Dc4O9krbLy39LZH3yZg08Wzz86VA+xui8KOPE41X1WKillpUDScbtxuy7nFSxJmv/ZKZLcZMSwvM0/fo23CWNV/QAyHk2AwyqVTh31+4xJyjgKATicqtM4Ziv8UH3SfeKaj+Jx1PBNd9JWnGouZcew7Ntqg0i94k8p+wU0+yPqGDdc8lGkn3mNLtqTm/gI8gJGtOeLPHrJNnhfqIuVzlXi7YG31zwXRLtU5eSzeKErDd7eyDn4xB6igGZBHwtkCJPYRyxXgtoMse8cq9O5SdTRPppJGkzR2v1q5o3LzLuvPXnmnWl2YJhLfGNvezb91yMxEQfwVaDVVqSLHTGi0vqzCuuPrQMtllk6kgPRSYKtRDCaqWMIhvlQgPf8J4i8Uo5ZzervZu0YODC0Hx5CmqZm0FlwJW3eoCtYm1eZos37FxgQ///v/3//xj+F/1VhH3foRkWlbuGf6wfFP/dfnIDxP04=
*/