// Copyright David Abrahams and Thomas Becker 2000-2006.
// Copyright Kohei Takahashi 2012-2014.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ZIP_ITERATOR_TMB_07_13_2003_HPP_
# define BOOST_ZIP_ITERATOR_TMB_07_13_2003_HPP_

#include <stddef.h>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_adaptor.hpp> // for enable_if_convertible
#include <boost/iterator/iterator_categories.hpp>

#include <boost/iterator/minimum_category.hpp>

#include <utility> // for std::pair
#include <boost/fusion/adapted/boost_tuple.hpp> // for backward compatibility

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/convert.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost {
namespace iterators {

  // Zip iterator forward declaration for zip_iterator_base
  template<typename IteratorTuple>
  class zip_iterator;

  namespace detail
  {

    // Functors to be used with tuple algorithms
    //
    template<typename DiffType>
    class advance_iterator
    {
    public:
      advance_iterator(DiffType step) : m_step(step) {}

      template<typename Iterator>
      void operator()(Iterator& it) const
      { it += m_step; }

    private:
      DiffType m_step;
    };
    //
    struct increment_iterator
    {
      template<typename Iterator>
      void operator()(Iterator& it) const
      { ++it; }
    };
    //
    struct decrement_iterator
    {
      template<typename Iterator>
      void operator()(Iterator& it) const
      { --it; }
    };
    //
    struct dereference_iterator
    {
      template<typename>
      struct result;

      template<typename This, typename Iterator>
      struct result<This(Iterator)>
      {
        typedef typename
          remove_cv<typename remove_reference<Iterator>::type>::type
        iterator;

        typedef typename iterator_reference<iterator>::type type;
      };

      template<typename Iterator>
        typename result<dereference_iterator(Iterator)>::type
        operator()(Iterator const& it) const
      { return *it; }
    };

    // Metafunction to obtain the type of the tuple whose element types
    // are the reference types of an iterator tuple.
    //
    template<typename IteratorTuple>
    struct tuple_of_references
      : mpl::transform<
            IteratorTuple,
            iterator_reference<mpl::_1>
          >
    {
    };

    // Specialization for std::pair
    template<typename Iterator1, typename Iterator2>
    struct tuple_of_references<std::pair<Iterator1, Iterator2> >
    {
        typedef std::pair<
            typename iterator_reference<Iterator1>::type
          , typename iterator_reference<Iterator2>::type
        > type;
    };

    // Metafunction to obtain the minimal traversal tag in a tuple
    // of iterators.
    //
    template<typename IteratorTuple>
    struct minimum_traversal_category_in_iterator_tuple
    {
      typedef typename mpl::transform<
          IteratorTuple
        , pure_traversal_tag<iterator_traversal<> >
      >::type tuple_of_traversal_tags;

      typedef typename mpl::fold<
          tuple_of_traversal_tags
        , random_access_traversal_tag
        , minimum_category<>
      >::type type;
    };

    template<typename Iterator1, typename Iterator2>
    struct minimum_traversal_category_in_iterator_tuple<std::pair<Iterator1, Iterator2> >
    {
        typedef typename pure_traversal_tag<
            typename iterator_traversal<Iterator1>::type
        >::type iterator1_traversal;
        typedef typename pure_traversal_tag<
            typename iterator_traversal<Iterator2>::type
        >::type iterator2_traversal;

        typedef typename minimum_category<
            iterator1_traversal
          , typename minimum_category<
                iterator2_traversal
              , random_access_traversal_tag
            >::type
        >::type type;
    };

    ///////////////////////////////////////////////////////////////////
    //
    // Class zip_iterator_base
    //
    // Builds and exposes the iterator facade type from which the zip
    // iterator will be derived.
    //
    template<typename IteratorTuple>
    struct zip_iterator_base
    {
     private:
        // Reference type is the type of the tuple obtained from the
        // iterators' reference types.
        typedef typename
        detail::tuple_of_references<IteratorTuple>::type reference;

        // Value type is the same as reference type.
        typedef reference value_type;

        // Difference type is the first iterator's difference type
        typedef typename iterator_difference<
            typename mpl::at_c<IteratorTuple, 0>::type
        >::type difference_type;

        // Traversal catetgory is the minimum traversal category in the
        // iterator tuple.
        typedef typename
        detail::minimum_traversal_category_in_iterator_tuple<
            IteratorTuple
        >::type traversal_category;
     public:

        // The iterator facade type from which the zip iterator will
        // be derived.
        typedef iterator_facade<
            zip_iterator<IteratorTuple>,
            value_type,
            traversal_category,
            reference,
            difference_type
        > type;
    };

    template <>
    struct zip_iterator_base<int>
    {
        typedef int type;
    };

    template <typename reference>
    struct converter
    {
        template <typename Seq>
        static reference call(Seq seq)
        {
            typedef typename fusion::traits::tag_of<reference>::type tag;
            return fusion::convert<tag>(seq);
        }
    };

    template <typename Reference1, typename Reference2>
    struct converter<std::pair<Reference1, Reference2> >
    {
        typedef std::pair<Reference1, Reference2> reference;
        template <typename Seq>
        static reference call(Seq seq)
        {
            return reference(
                fusion::at_c<0>(seq)
              , fusion::at_c<1>(seq));
        }
    };
  }

  /////////////////////////////////////////////////////////////////////
  //
  // zip_iterator class definition
  //
  template<typename IteratorTuple>
  class zip_iterator :
    public detail::zip_iterator_base<IteratorTuple>::type
  {

   // Typedef super_t as our base class.
   typedef typename
     detail::zip_iterator_base<IteratorTuple>::type super_t;

   // iterator_core_access is the iterator's best friend.
   friend class iterator_core_access;

  public:

    // Construction
    // ============

    // Default constructor
    zip_iterator() { }

    // Constructor from iterator tuple
    zip_iterator(IteratorTuple iterator_tuple)
      : m_iterator_tuple(iterator_tuple)
    { }

    // Copy constructor
    template<typename OtherIteratorTuple>
    zip_iterator(
       const zip_iterator<OtherIteratorTuple>& other,
       typename enable_if_convertible<
         OtherIteratorTuple,
         IteratorTuple
         >::type* = 0
    ) : m_iterator_tuple(other.get_iterator_tuple())
    {}

    // Get method for the iterator tuple.
    const IteratorTuple& get_iterator_tuple() const
    { return m_iterator_tuple; }

  private:

    // Implementation of Iterator Operations
    // =====================================

    // Dereferencing returns a tuple built from the dereferenced
    // iterators in the iterator tuple.
    typename super_t::reference dereference() const
    {
        typedef typename super_t::reference reference;
        typedef detail::converter<reference> gen;
        return gen::call(fusion::transform(
          get_iterator_tuple(),
          detail::dereference_iterator()));
    }

    // Two zip iterators are equal if all iterators in the iterator
    // tuple are equal. NOTE: It should be possible to implement this
    // as
    //
    // return get_iterator_tuple() == other.get_iterator_tuple();
    //
    // but equality of tuples currently (7/2003) does not compile
    // under several compilers. No point in bringing in a bunch
    // of #ifdefs here.
    //
    template<typename OtherIteratorTuple>
    bool equal(const zip_iterator<OtherIteratorTuple>& other) const
    {
        return fusion::equal_to(
          get_iterator_tuple(),
          other.get_iterator_tuple());
    }

    // Advancing a zip iterator means to advance all iterators in the
    // iterator tuple.
    void advance(typename super_t::difference_type n)
    {
        fusion::for_each(
          m_iterator_tuple,
          detail::advance_iterator<BOOST_DEDUCED_TYPENAME super_t::difference_type>(n));
    }
    // Incrementing a zip iterator means to increment all iterators in
    // the iterator tuple.
    void increment()
    {
        fusion::for_each(
          m_iterator_tuple,
          detail::increment_iterator());
    }

    // Decrementing a zip iterator means to decrement all iterators in
    // the iterator tuple.
    void decrement()
    {
        fusion::for_each(
          m_iterator_tuple,
          detail::decrement_iterator());
    }

    // Distance is calculated using the first iterator in the tuple.
    template<typename OtherIteratorTuple>
      typename super_t::difference_type distance_to(
        const zip_iterator<OtherIteratorTuple>& other
        ) const
    {
        return fusion::at_c<0>(other.get_iterator_tuple()) -
            fusion::at_c<0>(this->get_iterator_tuple());
    }

    // Data Members
    // ============

    // The iterator tuple.
    IteratorTuple m_iterator_tuple;

  };

  // Make function for zip iterator
  //
  template<typename IteratorTuple>
  inline zip_iterator<IteratorTuple>
  make_zip_iterator(IteratorTuple t)
  { return zip_iterator<IteratorTuple>(t); }

} // namespace iterators

using iterators::zip_iterator;
using iterators::make_zip_iterator;

} // namespace boost

#endif

/* zip_iterator.hpp
xA8oQxspqd2IFg0YLievX2TcG4Mdq3cHFSYd1dttOTaobRXrt7XXfyQlIskUa53kNoIIfOBFrLh+MbRoUXVPwiiroW4k/+g9KlW9FljluM9/LcRPzNBIgXr4yU7e/XHMr49ZOnpQwsmGx+gkyOZcJPxDWVu6UpA4rJLBEN4yeL3ysFV56Wa/LpEznB/Tu7P+asQhukjzulDU1Mi+4p0rAeNl1BW55SM9/DHWTJyze7QwfRCTi2qiNUQZ4VZ5GFIidg7pfx3r3QXiAasSvS3LqBVErgCn+gZtnrtyRHnF5EljeEQBMkVuHbblmt6fP7GIvwZS4mE7JP13V4844NkswLNU3F1JDxR4evkECv+dA0eNG1vgLXWBez0m6Fq8neyFOCgVveZhrKvOYtmJtg4HDNqwkzt8Fpp6xZ7TtLos1nPoz9VQx2HmZcR+4JvejB5fpBHMu5be3ZRfCMRMLkBUguS4/HA73d7qqvU+MXBHzUo81CZDMTKDk88r6mcxuahDRznpaNIHKRdswfHcuhQCbHc9CapaALeLoO2BsbUlWIjcIhlyA3+4ZNJM7iOwKY1TqunLS7k0hMUUzBu+0RnKYlAtcEUAr6VlnUiIFQvQqknK2Kh5tUC9mXI4lobOp5mhR5rcEqYOeAN5DBVXgcIXHo/UabM5SM5z4m2kYeGTCXK9JYOqt8G9Lhx8WOeCQf2bvbAbsoidgOI2iij1XfLPUhpcri7+FWYmx7WyItCQPpP4bFNwAIqhE8NxLfR+zMbtjqvCaJHq9iHkVZOJU5gsBeM6ucChMN6ElsWPuSJX3SISWMGl9Cae9ij2DTU3brPQQ73W5ZwwII/tFBEVh/GSNtQROsONGIM23X5KBanEdgC+X3fJYPK1AElviKapQQASOhk3SvSaSo317xv4qyMeh9U1xm7gV+BhWZBek7rWY6DL9YYSvvcBR4VPJi3Z7khKhAdz1oFWHxdr3jCCuhk08kZQDXhlWmOmBy7VsMlRVVgyrGJsBXQ308xtmSBJVvhJ5PWDBEabHFtRH3rUXdL1GvIAACz/0/gC2vJ+h92gnk0GSrv6RoQAK9bd28S8Z5Ufr6zk163PTYKYtgIinBNbyQniVOD5W/z0ugNfWcoRvoubMs+HigxakwfpOxAXGRlEr0ku4Pv6KeQUbseQPzSTpbHo66qekvziurD6JaUV+5h5uJSFvrNfhTDIgPdmN2EDP8aOMVbrOSbWPez4QdFKUfuA69xXUpHfXYr9f5lBAQRkg2ACTe1BhemjMkwVmok/JFmUsq4b+jRnS9PfQl/BQp69hBws5e967kBhUfs+881P5XUYGSb8J+MNsoKOO4OT03oC738jOVW+YstnCXf57UTlLOzvobdug9NIMgbmKPbzJzuNlWWCv0Y7km7Q7+StsxH1MjammaaONaFWBi+ayhQSZNLZYWW2wRYLJWZQYo7rHQLtqQOWFQbpW/KhNIikqLJ/lLHITIY5PnK6++ZjdBQTZJut5RKDT20HGj5hPRePJZKpNvvhrAKl5ptXg5SkAwO3Lvs1yBqATY8e/4azMhPWjGLLrJfZOcrWJHQXlUJxbIPryqggDwsJXKKiMKPJgIkahvZBwr1/g5ktGhtYdTJQ+igQ0dCqZqNtnCUAsprq/itTS0GCmAmBMD9wipQSJ7UOcCS8S6cQjXxT5m21mmFzhlhS/7INMhm9N+UQ6fZZ0oj88GgYt/WVju7vP9+iFNUW5Q1NkhKWjBdcQlSgYW7yr1OLr1mfISHwFM4R5ZkYCAoUcFlxChHL87RMLuMf3j7oRMXl3mqXg9hT8WkZsA5nnTDrJkxtblpTiWDxoScgkBhvnGLbZm3KEUEklRZvcpjKtK8yL4/ya8u6xcFUUGSRfCvyJlFkA+j1yWlo/prcBjcm109bqyDJ+gSeF3F9IlWkRzPE6B+OUenA8LTx8xWV5SPbD+/Lw2iZNfxkVRJ+eWNyFlARJv8ZVCAUbcilV7DY2GgNPIrFc6kg6Hf6ghG5XswlvsglYvhtLOYJp7j85TLCj8LFq+Ht2FhPEPgBBTLmOp7pHGyOylXa37tV2VDml8eXYReOP8xgnpmucC9p/KezygW6UyUuT4cHAACQO1AurEipoOrvhfX+66y/EalULWD8Fexx8uVhWi4FxMMOPr4Oo4HTaZT0H7cbffv6DZZ2NTAhbRwtf6byYCzkDMbP2Ix0wQx6J0VXRQd/4puVVpXRSo6nbSlBcj1q0ZdWDNPV6rbLBvSqgY6ldT68Xjj7j1zFBDLDFttKBciK6mAl9fxuW01itYQWf35O6f0/Zc4ZhXPJ0XbEvThtM63FYibbopPkdrdZVuTe+S6WPUS0DdtQfCnTi/GWWCJ9JsYG9D8iDiOjJIrAOg29Ajg8jF1/QUxIojO8/t7xoj5AVm0HJE5MSbQ5arFM44jIQJzoZhmGRX/bFeZ8LJY8bH5eFoB9e4YIkxgETRU8DXnniDWNPsCukNatwT05fpIbUeEmC+Xj0/GBcwQosCWhqyMUcteN6iL9/p4C8/xemFqtqhMjH3q+KVdA96gpQ2RevEIb82DlnWPuYPdxAkXD6oi+Frn54QtNEkvBbnlTh8vkH6KF5FDq1x2DBv4vn5leAA0LoJ8rJITdG3fpMTy3EiyQpxB8/ApBfsDvFi4hZHDqh7VulBKblhReq3BrY1vHd/hwfmE2FksF494dyvH4G/3+V7kt6Cr9vKLLz0LwacHFCaPk3/kkVNTG3zWKSBuTUQZmGemziZs4lDfJeeRiYDeh5q+HVLl5KfnoG+eE4/C7/Wr1mDnzW/TI0XrvRIEvs0KHAQmssM/3bGh3BCmL1A3pEO0pQneq8rfYYVsZoctYRR5n8X2tLpwxwFiIAQZDZfUwAaZ8/HShmsPYNb+Eew2tZgEZabwcNXrMe6Dl7nXSl35i0PLAYsmwUCfriPTNCAcNpInGG8PMD5YufrorCGIhsXgwMC6IlT+AL4mXTd5pRS8st8Y251yXy2nARS1SrP8qMdmZ/uIdzxM+fPVgXOrqAFr4z/rzk2qmWaCy9XNLt/6VPO6I5BOn5/YjE+onZLBLM0u5QyAMVrCIwMis5diiaogw+40boyKn1QDBimflJkk+iilHCFskyHP19PrzFPx/dNkuiBIMxl+HJMSnXYj7q7+TqbyQXEUOajW8SB9O+kfW4u2BFl4H232HSw8xgI1sreP4RGHXLoAQIjelb+fyEp801ntJglGI4yAVq0ojv1i+IIHkzHA6oZDfutmwvLsFxUHCYwwOg7pGtPzrwxXzbXbARo0UdqmpRkq4hdqp83OblXtUZVx+Q9YZzrI5q3LVyXRJD2R9Pz5fj3lBGoSnkZOFuD8nnxZaPFx5HtZFBhVrQgG5ZFxAlaGWknoblxBy5V/oX80Zw6C2i1O2nClJ1ZJaPNtWdyMpGyK8VuNSZ8Z1Ekh/JpQoUn55ZwzmZBJ4KHwgQfjv2jfwoIOLmySCh6/knLOeI7BcLmSBxdXOJfoNL4b7bORvlpmZ7NH7NkoneY5F2W4TesfaZan911pa566ktEjEhbx3yhVYjtuFKj2a3CnKaqNc+KTuS89AFdD/TYXC/kOKxP+QcmiND9qcvQS6SSJPAC5q1J/6irvNCDzhwZAUy+WISaeVl1j80yHAWaTd2efexl8Dz1Pd/k9E3IqJl46ZJ+ZhF8ROH+bk4+OFb73S1zOd4bQZCmYhxR5/gmWOEFN0HihExHUAnt85fqW9S9TrMBd+WPGmVOWCnM6uy7PnD6fwDhhtI/eoOA5kYMU0KDIloaeN7LZxx6+DnSirjV6h1bSAJ6zmU9vDBNU58Gy7xOi0Q2AARWzA0IxDLdwpxFXVLjKalkUis94nGvG5e2rTHYjrExexqXuf+C9e4gbqvy7jCZg5DxWb85/28QSRKQO7VUZBSCpzgkTLLCFSz3UTm84BXx9JXRcO8veBLBw30MTtr3fwfgszwvtJGQP4wbtxsZX5bawoFVWJAJyx1XyWGCLt2HwzfDs1sdnTsX+P+9eYgjwS6BuXt6fqOAOYkP/uqscL1FhYkx8RXcbYj3dyUZEP8/pcOPs8+5vWpYRycFeE5GUB8Bx9Tth4RBdpM+yQVnj/72MpnEBT/CH9uQDoij5UD8skq3x33EJMe+KzQSIAj5E5RjixgonLoue8cz1FQ/iu4Ln1JVoUGSwXWK8+PVj0oYNFdj5hAX1Kq1nsUeBKU7qgZrYumgLgWH6s8vYZIYZ8MQZzmggzb0XSsMsowbVAAYwV7Y+IENXwtvJTw9ocOVRocK3VxaDwftl+cbRsk2YutCdl/ko4U0ljaKVSakzw6jJxTkPzQ7f1VU1s6Drnw4QECGmVTmtIip53GkYLAdab49w09B8TybV9EaWx5gldYZU7O10iA1VLGP8AY+Z/o9mU3/TRuzRcYzMNFWA0MIHqYOBCAcHlCfQggn0AFoOWgzNRSoXtjzkY3eB1L2g35afni8g4RGiiT2vQxhWVTqNZzHvEY5xjhyFxJh+YEg3EqprRaCC5mC9iI5/G8EzBB4FcTtu+J4oZ1JmioL3HPVvXA+qz0oFqRNXNF0nQlVkehQ6U5d4eka+5WpuVIaDx/7GkJkaQoEneEF87RHMAjVKSPx+eNv33x6fk64Hspkoyc63FXQczU7uGegjzqAil4KnsX34u/SBygEE4qj8NRz6te9TKsJFuFEqf8bCEe5ufwytjvmq5S8uho6761n5EpKKQzIo1m2OQAO0TscbS5HxiDXLKFndK9uqHLQeiYY1AOQcrLFelvVJjRXV7bD/nRFLnR984olch1l7lK1lvpKnnp2o39W1MUs0jDSgLt5kQFZLiqfIxKoXxUZC6gtWOOuxyKDX4YubO+yU9CeRIQAWeutNWmgw2DS87hEadhQsLFDw4ov84sD2+PcB/Xp9v9oJpaxHnbrx5KQUT92fPlvncrVXwcaX+Tw/PUW616d+YHXexzIWGAlByCJJWF/CnfNq7E0FVD8TRORgb+ZxU33IVbgDudZQJY6u/GvTAAwnLi+P/2zuFlfk/R0LEnefn2zcz+JdLxeUvwavjX1zAyG65M5zsw6PWsmatNPl4OuYVEym040pkmb1O+APVA3QXz+AAKxyE43jG1P7z33w9P7zL569XimfG883bKORzs6QEzeXfka1FGJtT/6UX3eNe6Uz/nuL405+DYfNDFFE0tbspAvsWEkpm3TK04ZFA1tnUeJ+t4Z/zkWRRkazwQZaANYVTQ7dmV4JiOYTKBy6grMCcRrtyf3pbINy+mRIGFYRwgOPNRmW6/mFIxfRp1dp8jcvJWvkQreaoxwjOgk9HXWrAiS0rW33zFAOZ9VG5DNDty9q3PcWmiUl5n1S0fxlnRDuSpfu6U4cb0gt8SzZpOtzCm+D1M2anddZVt66BMdPq5oEPGpwvx5QaIWbW0ocLGAiRV2NystnQS/8Gfs+XZPuKch3y03IrFRpu2W5uPh0aNJRBY2VbZcTDUysj779b+xkNtYd2E9CxWg5xq+JJe45PvDa7iMxeqTxA6H/EkOsDAADAlpPIxgRDttfm4anF1IrxAJBUulh7NXnj3pyONcVxbUQbXjpbXe6XbcOM6W55+Y4yHsL8sQ1zxHKCJ0gsQJqrltOT8/n1j9We4HxkZESQTeuyYP6kbY4u9714eb7gZhl3U8E2zUUATNtoqWXMrpPbM79Gnpn0J6cF5WnEwc3Pz091Gf/0y5pphQjjSf6hNEXl5CYRP0jBoqE/kEqaqoaQpr9lmaO6h1/c9+nfm4yB3fL4fKpwW4/27FSxnWeOTgwO2aMgTDouYu5LEAQ5fRprfWOcntdiIZyLo7kWKRF8YGUwC6M+hcB8UYbqyZLaBCF1/3nHlG7gIovNJXtI9EJbCW/1nDbszmH/zllUYH27GelmvUVuBMYMERTHDsMYtG3eTM4dj12AGE8o9sEvHc0dRPRnj3UO2Q4XrDujHl4fAETdHKmj7P138Uf3zqpf7tQhhAcwSQxWeStETQMxf/24HO7n5pDr4yQXAJVNW9rrkBLDvRQXaALbhVQhtdHcm+GmmIJGo8IKA+D7DynDmRnQhkjB/MnA6+FRlbWUTsNABR9d3s+giWjgkv413ekwPi1XSlpKLaO5RT7yvinYy6UqDfS8QT7pnzkmyq5T77cWddofskRtzqhcbFnHdasVGOB9FP40pUUkoU6ML+Qmkb2dpZKNklG8Iq2XigsM5iGEMZjyC0tRQGSt0TsopkM9oCJN4EqZFA/8+CeNkqQO3vIBAlbWqmxoylaz6fe0LdM3Cdr3LUzDVUmdymCZn1jZ9IFJsDjz8biZYYhE/McD2rJmYwvp3iCpMqtMi80fny5fj4303lElZg+C8W1BM3/Sdg/wBwN1EPIYvdyEAy0kl8lTgARDCOjh/IHZnLBVbCeuyH4kTjIwj6YKYKclEHF49UH6IQAAyFeBTFj1/w2p5ptqvH1SGzN8g8WBHe5ZteAQH0HZ2mvbnlKJfmUjHH/EonYlR5aSgl8Ne7Vdrz4EcauSs89yLF+iJKL4s1uj6CjWUpPxWa9FKGHFcYuOBMiYQTDzI/kubNCGiC397JrRJa2dSWacGr2hgK0TWxLBl3yb68MLK8Xr9ILYpcZwOaFuKlVMPCKyyfsWsk03oWRx0bdowd5bqB+dF/aAuW/YuizdQzOUk2eeHjmuZnDyZQ00kIc2MTdDzv4Ipu5fK1fJr2scefX//GrdvjKOga1cGE8HeHraISlcrEoLBKAuDOJ1/ouQhN1MjlPIsSsJC3EndTtw5QKxp89NQjd+zaMpcTyMrQx1xxABQuew0m2v7RrvlWjnuT523MO48LcJqE8uT/7kHmB3GtqG0dZMMB/U1KEU3hi94mi5ksay69KFyMFUePWq+0MjoDHWzoF+zIie3uLg5kcA4ircNFbeRWyWAxJhA6Z+9dGBZ5G4baTBd69/Vbg3061/YFFAVfG1jaRr1hawM4AwReoawDltzxjnQHT5JGmsLO4hHxjR0nWDPmTKgUdAzViBvGUNIO1JoVb5jq5gwg6+tomXvPFJ9uHXUSgqRlLuVnJMD1InqyYJiwNUmt/WAWl9KhKijDNNNdKoE6gOrl27j+5u0Tw/6ncauNzpuOkH6aaMSQZD6Luo/B2uouxqC+1S7Jbj2iAlyhR+4w8yNCDw/w4JTq2aQSuepHSWTDohKXpCGe1whjmUwgiBNq+PNLszKZCHC9Uv+WFSg9whJYbAafYGyi3/lFlgJW59Q52kME4fJsAITrGId01vDEovFjRzZvijpp1R9QlrwoJRZlaGhpOR8zzqd2UqE1jIkyvHZUO/hpvmSI6Yz9o5S5BAppCUG/2ohH4WHE4ibEMn0mt6YfF45BZg0kVLs8NZ8q0eAX78sIkAkLWC3FRt7juQmv/75sbOc2dAKnYRoSFLZz7YxUL92ECjDfgD96/8ukKxGJid7UgpTXo9ruTNFkmvhBG+kO2+2A32j1Tf+9ddwx/FIBeEy/PYjTvTnpMzDFMEJ59kS5jrcBSJdQaDLYwSZZWy7JfyZD8yAoNVtEnQ4Gu7KG7vrubNPNULPaoHzSTudaZ5735e3h4pbPA1xlJFQlR+eh9xLLbHpMcQzIYWjKS73IbI
*/