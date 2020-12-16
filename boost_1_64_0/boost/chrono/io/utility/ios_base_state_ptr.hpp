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
pF3l3jLe6695/fxYfOOY+pUU/Y2DWcel2ZLm9hKnUlm8hp6zAl9Dfa5jcDbr3liYHLPuzfLTVaXlFWWW5lvqXk6WRVdF/9GWfadsGioej7OsJ5VRPE+/x+vj1vtVP5dekmNJXA+sxroxsWrd8KSVdQOsUje4Bg7ThPx6hvmVx/x7NUj+zWLLeRHzbxbb7qjZ/vlXiO/bgO02/ba25C1eIX15x+MtLXmTr9u5dnLsbBWP76gIJOAATHhTXE8TV4izKb6dOoRY8y1g/iZLHP3l+yixxvWWbPecX1vIdNv85Ev+Jc225+dQ2pmfeo2EEPlbdb281bNrv14e/Fa7Xt6a2ae7Xp6n7EuZ1iTe/91gNsGt0pNWlLfn/s9Eb0dhmRvtQGmN7w5m3nwwu05P96/o6W4XPd1Lr+VfkDut7+L4RjufT5w8Z16dno56OlkHoIVlHYBNMj9f2gvRFb3INQE+0f1Z0icmx+Lx/36G/ZrarW85J/YkNUffcd36eHMONLV0E/zmzl9nAlwLhoAbwVBwG+ji3Ph64HtgfdCcQxgBjgAbc856NHiVwTn2YBj4CBgJvgU2BN8FG4EHuJ/C12As2Iz7KDQHE/RcYPZrsC+ltd9c4NeR/sbgbrAJuIdzsPfyeo/yOt8Gz+WaBpdTu/Y09684yH0rPgVhlh0CvwC/Af8BRnKfivbcn6Ij96eAUVsVv8XB6UyfmY67mb428BcHtqUWsgO1dB29+yUwnZ1ZDt24D0J37rsxkHNyh4Kb6f8xaslep3bsK7Af02n6bwGa/hPBYZwLOggcRTvTze9RfBMHSHcK0z2S6R5DLeBYcDw4DpxIbSOMmgBmgZPA68HJYAW1k5XgdPAlaiJ3MNx+aimP83gDA8epDTSPJ4AzwF60U+PJbz18NwbQeC7gWhZLWC8u0eFgGM5VNZys3WCyJxiqfPutpMKkMNwshqsn+cF3C54vl3OG80Dz2MXMnwJqJfNZ/wqYngq+11u1s43BdUqvXSVrDaRzTY1SsB9YBg4Ay8GhYA54IZgLzgXzwGvAi8H7wPngZvp/ACwA/wwWgm+DReB+Hj8ILgI/pp37mPCdGc8aptO6j8nlvP7lYDz3nUjmnPEpnDM+nXPGSzgnfC3njt/Aude3UGtaQTvXMOF7p7z/2tcwoda0Efgiz/syNbo7wNHgK+BY8FXrGiZ8dl/E+KxrmPQxPPElg03AweBU8HxwFniB4U0X32HYXm9Sp7e2yniYSsaXFOA672D4u8BYzklvDW4C21N72412c/+Zq3ZhL4CXMfcWrIQxNaRDv6/Tj/679KOzkLfVaUiTdoTVSkea/33Yv6wlXYqwG8zwMPthTsDE/YB0wcyBKYdZB/MQzG6YQz/UaU3rfnW//6XfzzL+7y7GZ/KZmf//hWWMfwvnn3TjM7UjzI/ReC720f00cuYcZV/HtUj3K9AvQkbrfoecouKCjFLbmBn9cD5+wLGWxuBH4i9U9838I6bmNUr91m+VtMXa1inV6bGNS5VS33ApTDOuQXUc1676+vqoCnn1/msa89rpd4rieJ3MmeQ189iYoPmSqv2MknzBy0vQ/uPzxV875IxT1ondirAxSP9h5E9ETHtnc3RpOeNd0c76rpCIRmE6/47guF/a5VypoDXNcGMfoOnG80v3kO9aCyUNYb55mDqtpcVlhZnoYs2SYylK6T6z3BrKze237jDHhzmOWMh1EqovxyQOEH0K0wZmp+k/QakKXzkuZDEGq8P0m6rX5D4i9svUfHM+PveKdfeTvtjq6jnjOZ95zv7cEpa3Pj4iYDnHgRfIOZrirBGcV2s/b48E0RGUzcv2laU7cLnpMo3lMR3OMzQToBw=
*/