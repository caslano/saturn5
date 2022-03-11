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