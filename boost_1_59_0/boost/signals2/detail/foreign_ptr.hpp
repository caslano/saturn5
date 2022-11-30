
//  helper code for dealing with tracking non-boost shared_ptr/weak_ptr

// Copyright Frank Mori Hess 2009.
// Distributed under the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/signals2 for library home page.

#ifndef BOOST_SIGNALS2_FOREIGN_PTR_HPP
#define BOOST_SIGNALS2_FOREIGN_PTR_HPP

#include <algorithm>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/smart_ptr/bad_weak_ptr.hpp>
#include <boost/utility/swap.hpp>

#ifndef BOOST_NO_CXX11_SMART_PTR
#include <memory>
#endif

namespace boost
{
  template<typename T> class shared_ptr;
  template<typename T> class weak_ptr;

  namespace signals2
  {
    template<typename WeakPtr> struct weak_ptr_traits
    {};
    template<typename T> struct weak_ptr_traits<boost::weak_ptr<T> >
    {
      typedef boost::shared_ptr<T> shared_type;
    };
#ifndef BOOST_NO_CXX11_SMART_PTR
    template<typename T> struct weak_ptr_traits<std::weak_ptr<T> >
    {
      typedef std::shared_ptr<T> shared_type;
    };
#endif

    template<typename SharedPtr> struct shared_ptr_traits
    {};

    template<typename T> struct shared_ptr_traits<boost::shared_ptr<T> >
    {
      typedef boost::weak_ptr<T> weak_type;
    };
#ifndef BOOST_NO_CXX11_SMART_PTR
    template<typename T> struct shared_ptr_traits<std::shared_ptr<T> >
    {
      typedef std::weak_ptr<T> weak_type;
    };
#endif

    namespace detail
    {
      struct foreign_shared_ptr_impl_base
      {
        virtual ~foreign_shared_ptr_impl_base() {}
        virtual foreign_shared_ptr_impl_base * clone() const = 0;
      };

      template<typename FSP>
      class foreign_shared_ptr_impl: public foreign_shared_ptr_impl_base
      {
      public:
        foreign_shared_ptr_impl(const FSP &p): _p(p)
        {}
        virtual foreign_shared_ptr_impl * clone() const
        {
          return new foreign_shared_ptr_impl(*this);
        }
      private:
        FSP _p;
      };

      class foreign_void_shared_ptr
      {
      public:
        foreign_void_shared_ptr():
          _p(0)
        {}
        foreign_void_shared_ptr(const foreign_void_shared_ptr &other):
          _p(other._p->clone())
        {}
        template<typename FSP>
        explicit foreign_void_shared_ptr(const FSP &fsp):
          _p(new foreign_shared_ptr_impl<FSP>(fsp))
        {}
        ~foreign_void_shared_ptr()
        {
          delete _p;
        }
        foreign_void_shared_ptr & operator=(const foreign_void_shared_ptr &other)
        {
          if(&other == this) return *this;
          foreign_void_shared_ptr(other).swap(*this);
          return *this;
        }
        void swap(foreign_void_shared_ptr &other)
        {
          boost::swap(_p, other._p);
        }
      private:
        foreign_shared_ptr_impl_base *_p;
      };

      struct foreign_weak_ptr_impl_base
      {
        virtual ~foreign_weak_ptr_impl_base() {}
        virtual foreign_void_shared_ptr lock() const = 0;
        virtual bool expired() const = 0;
        virtual foreign_weak_ptr_impl_base * clone() const = 0;
      };

      template<typename FWP>
      class foreign_weak_ptr_impl: public foreign_weak_ptr_impl_base
      {
      public:
        foreign_weak_ptr_impl(const FWP &p): _p(p)
        {}
        virtual foreign_void_shared_ptr lock() const
        {
          return foreign_void_shared_ptr(_p.lock());
        }
        virtual bool expired() const
        {
          return _p.expired();
        }
        virtual foreign_weak_ptr_impl * clone() const
        {
          return new foreign_weak_ptr_impl(*this);
        }
      private:
        FWP _p;
      };

      class foreign_void_weak_ptr
      {
      public:
        foreign_void_weak_ptr()
        {}
        foreign_void_weak_ptr(const foreign_void_weak_ptr &other):
          _p(other._p->clone())
        {}
        template<typename FWP>
        explicit foreign_void_weak_ptr(const FWP &fwp):
          _p(new foreign_weak_ptr_impl<FWP>(fwp))
        {}
        foreign_void_weak_ptr & operator=(const foreign_void_weak_ptr &other)
        {
          if(&other == this) return *this;
          foreign_void_weak_ptr(other).swap(*this);
          return *this;
        }
        void swap(foreign_void_weak_ptr &other)
        {
          boost::swap(_p, other._p);
        }
        foreign_void_shared_ptr lock() const
        {
          return _p->lock();
        }
        bool expired() const
        {
          return _p->expired();
        }
      private:
        boost::scoped_ptr<foreign_weak_ptr_impl_base> _p;
      };
    } // namespace detail

  } // namespace signals2
} // namespace boost

#endif  // BOOST_SIGNALS2_FOREIGN_PTR_HPP

/* foreign_ptr.hpp
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
*/