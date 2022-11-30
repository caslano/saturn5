//  boost/chrono/utility/ios_base_pword_ptr.hpp  ------------------------------------------------------------//

//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_UTILITY_IOS_BASE_STATE_PTR_HPP
#define BOOST_CHRONO_UTILITY_IOS_BASE_STATE_PTR_HPP

#include <ios>
#include <boost/assert.hpp>

/**
 *


 */
namespace boost
{
  namespace chrono
  {
    namespace detail
    {

      /**
       * xalloc key holder.
       */
      template <typename T>
      struct xalloc_key_holder
      {
        static int value; //< the xalloc value associated to T.
        static bool initialized; //< whether the value has been initialized or not.
      };

      template <typename T>
      int xalloc_key_holder<T>::value = 0;

      template <typename T>
      bool xalloc_key_holder<T>::initialized = false;

    }

    /**
     * xalloc key initialiazer.
     *
     * Declare a static variable of this type to ensure that the xalloc_key_holder<T> is initialized correctly.
     */
    template <typename T>
    struct xalloc_key_initializer
    {
      xalloc_key_initializer()
      {
        if (!detail::xalloc_key_holder<T>::initialized)
        {
          detail::xalloc_key_holder<T>::value = std::ios_base::xalloc();
          detail::xalloc_key_holder<T>::initialized = true;
        }
      }
    };
    /**
     * @c ios_state_ptr is a smart pointer to a ios_base specific state.
     */
    template <typename Final, typename T>
    class ios_state_ptr
    {
      ios_state_ptr& operator=(ios_state_ptr const& rhs) ;

    public:
      /**
       * The pointee type
       */
      typedef T element_type;
      /**
       * Explicit constructor.
       * @param ios the ios
       * @Effects Constructs a @c ios_state_ptr by storing the associated @c ios.
       */
      explicit ios_state_ptr(std::ios_base& ios) :
        ios_(ios)
      {

      }
      /**
       * Nothing to do as xalloc index can not be removed.
       */
      ~ios_state_ptr()
      {
      }

      /**
       * @Effects Allocates the index if not already done.
       * Registers the callback responsible of maintaining the state pointer coherency, if not already done.
       * Retrieves the associated ios pointer
       * @return the retrieved pointer statically casted to const.
       */
      T const* get() const BOOST_NOEXCEPT
      {
        register_once(index(), ios_);
        void* &pw = ios_.pword(index());
        if (pw == 0)
        {
          return 0;
        }
        return static_cast<const T*> (pw);
      }
      /**
       * @Effects Allocates the index if not already done.
       * Registers the callback responsible of maintaining the state pointer coherency, if not already done.
       * Retrieves the associated ios pointer
       * @return the retrieved pointer.
       */
      T * get() BOOST_NOEXCEPT
      {
        register_once(index(), ios_);
        void* &pw = ios_.pword(index());
        if (pw == 0)
        {
          return 0;
        }
        return static_cast<T*> (pw);
      }
      /**
       * @Effects as if @c return get();
       * @return the retrieved pointer.
       */
      T * operator->()BOOST_NOEXCEPT
      {
        return get();
      }
      /**
       * @Effects as if @c return get();
       * @return the retrieved pointer.
       */
      T const * operator->() const BOOST_NOEXCEPT
      {
        return get();
      }

      /**
       * @Effects as if @c return *get();
       * @return a reference to the retrieved state.
       * @Remark The behavior is undefined if @c get()==0.
       */
      T & operator*() BOOST_NOEXCEPT
      {
        return *get();
      }
      /**
       * @Effects as if @c return *get();
       * @return a reference to the retrieved state.
       * @Remark The behavior is undefined if @c get()==0.
       */
      T const & operator *() const BOOST_NOEXCEPT
      {
        return *get();
      }

      /**
       * @Effects reset the current pointer after storing in a temporary variable the pointer to the current state.
       * @return the stored state pointer.
       */
      T * release() BOOST_NOEXCEPT
      {
        void*& pw = ios_.pword(index());
        T* ptr = static_cast<T*> (pw);
        pw = 0;
        return ptr;
      }

      /**
       *
       * @param new_ptr the new pointer.
       * @Effects deletes the current state and replace it with the new one.
       */
      void reset(T* new_ptr = 0)BOOST_NOEXCEPT
      {
        register_once(index(), ios_);
        void*& pw = ios_.pword(index());
        delete static_cast<T*> (pw);
        pw = new_ptr;
      }

#if defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
        typedef T* (ios_state_ptr::*bool_type)();
        operator bool_type() const BOOST_NOEXCEPT
        {
            return (get()!=0)?&ios_state_ptr::release:0;
        }
        bool operator!() const BOOST_NOEXCEPT
        {
          return (get()==0)?&ios_state_ptr::release:0;
        }
#else
        /**
         * Explicit conversion to bool.
         */
        explicit operator bool() const BOOST_NOEXCEPT
        {
          return get()!=0;
        }
#endif

      std::ios_base& getios()BOOST_NOEXCEPT
      {
        return ios_;
      }
      std::ios_base& getios() const BOOST_NOEXCEPT
      {
        return ios_;
      }
      /**
       * Implicit conversion to the ios_base
       */
      operator std::ios_base&() BOOST_NOEXCEPT
      {
        return ios_;
      }
      /**
       * Implicit conversion to the ios_base const
       */
      operator std::ios_base&() const BOOST_NOEXCEPT
      {
        return ios_;
      }
    private:
      static inline bool is_registerd(std::ios_base& ios)
      {
        long iw = ios.iword(index());
        return (iw == 1);
      }
      static inline void set_registered(std::ios_base& ios)
      {
        long& iw = ios.iword(index());
        iw = 1;
      }
      static inline void callback(std::ios_base::event evt, std::ios_base& ios, int index)
      {
        switch (evt)
        {
        case std::ios_base::erase_event:
        {
          void*& pw = ios.pword(index);
          if (pw != 0)
          {
            T* ptr = static_cast<T*> (pw);
            delete ptr;
            pw = 0;
          }
          break;
        }
        case std::ios_base::copyfmt_event:
        {
          void*& pw = ios.pword(index);
          if (pw != 0)
          {
            pw = new T(*static_cast<T*> (pw));
          }
          break;
        }
        default:
          break;
        }
      }

      static inline int index()
      {
        return detail::xalloc_key_holder<Final>::value;
      }

      static inline void register_once(int indx, std::ios_base& ios)
      {
        // needs a mask registered
        if (!is_registerd(ios))
        {
          set_registered(ios);
          ios.register_callback(callback, indx);
        }
      }


    protected:
      std::ios_base& ios_;
      //static detail::xalloc_key_initializer<Final> xalloc_key_initializer_;

    };
    //template <typename Final, typename T>
    //detail::xalloc_key_initializer<Final> ios_state_ptr<Final,T>::xalloc_key_initializer_;


    /**
     * @c ios_state_not_null_ptr is a non null variant of @c ios_state_ptr.
     * @tparm T
     * @Requires @c T must be @c DefaultConstructible and @c HeapAllocatable
     */
    template <typename Final, typename T>
    class ios_state_not_null_ptr: public ios_state_ptr<Final, T>
    {
      typedef ios_state_ptr<Final, T> base_type;
    public:
      explicit ios_state_not_null_ptr(std::ios_base& ios) :
      base_type(ios)
      {
        if (this->get() == 0)
        {
          this->base_type::reset(new T());
        }
      }
      ~ios_state_not_null_ptr()
      {
      }

      void reset(T* new_value) BOOST_NOEXCEPT
      {
        BOOST_ASSERT(new_value!=0);
        this->base_type::reset(new_value);
      }

    };

    /**
     * This class is useful to associate some flags to an std::ios_base.
     */
    template <typename Final>
    class ios_flags
    {
    public:
      /**
       *
       * @param ios the associated std::ios_base.
       * @Postcondition <c>flags()==0</c>
       */
      explicit ios_flags(std::ios_base& ios) :
        ios_(ios)
      {
      }
      ~ios_flags()
      {
      }
      /**
       * @Returns The format control information.
       */
      long flags() const BOOST_NOEXCEPT
      {
        return value();
      }

      /**
       * @param v the new bit mask.
       * @Postcondition <c>v == flags()</c>.
       * @Returns The previous value of @c flags().
       */
      long flags(long v)BOOST_NOEXCEPT
      {
        long tmp = flags();
        ref() = v;
        return tmp;
      }

      /**
       * @param v the new value
       * @Effects: Sets @c v in @c flags().
       * @Returns: The previous value of @c flags().
       */
      long setf(long v)
      {
        long tmp = value();
        ref() |= v;
        return tmp;
      }

      /**
       * @param mask the bit mask to clear.
       * @Effects: Clears @c mask in @c flags().
       */
      void unsetf(long mask)
      {
        ref() &= ~mask;
      }

      /**
       *
       * @param v
       * @param mask
       * @Effects: Clears @c mask in @c flags(), sets <c>v & mask</c> in @c flags().
       * @Returns: The previous value of flags().
       */
      long setf(long v, long mask)
      {
        long tmp = value();
        unsetf(mask);
        ref() |= v & mask;
        return tmp;
      }

      /**
       * implicit conversion to the @c ios_base
       */
      operator std::ios_base&()BOOST_NOEXCEPT
      {
        return ios_;
      }
      /**
       * implicit conversion to the @c ios_base const
       */
      operator std::ios_base const&() const BOOST_NOEXCEPT
      {
        return ios_;
      }
    private:
      long value() const BOOST_NOEXCEPT
      {
        return ios_.iword(index());
      }
      long& ref()BOOST_NOEXCEPT
      {
        return ios_.iword(index());
      }
      static inline int index()
      {
        return detail::xalloc_key_holder<Final>::value;
      }
      ios_flags& operator=(ios_flags const& rhs) ;

      std::ios_base& ios_;
      //static detail::xalloc_key_initializer<Final> xalloc_key_initializer_;

    };
    //template <typename Final>
    //detail::xalloc_key_initializer<Final> ios_flags<Final>::xalloc_key_initializer_;

  } // namespace chrono
} // namespace boost

#endif // header

/* ios_base_state_ptr.hpp
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
*/