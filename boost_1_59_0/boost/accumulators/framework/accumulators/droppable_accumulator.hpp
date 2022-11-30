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
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
*/