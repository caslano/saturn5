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