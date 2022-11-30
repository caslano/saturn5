// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_OBJECT_POOL_HPP
#define BOOST_OBJECT_POOL_HPP
/*!
\file
\brief  Provides a template type boost::object_pool<T, UserAllocator>
that can be used for fast and efficient memory allocation of objects of type T.
It also provides automatic destruction of non-deallocated objects.
*/

#include <boost/pool/poolfwd.hpp>

// boost::pool
#include <boost/pool/pool.hpp>

// The following code will be put into Boost.Config in a later revision
#if defined(BOOST_MSVC) || defined(__KCC)
# define BOOST_NO_TEMPLATE_CV_REF_OVERLOADS
#endif

// The following code might be put into some Boost.Config header in a later revision
#ifdef BOOST_BORLANDC
# pragma option push -w-inl
#endif

// There are a few places in this file where the expression "this->m" is used.
// This expression is used to force instantiation-time name lookup, which I am
//   informed is required for strict Standard compliance.  It's only necessary
//   if "m" is a member of a base class that is dependent on a template
//   parameter.
// Thanks to Jens Maurer for pointing this out!

namespace boost {

/*! \brief A template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

\details

<b>T</b> The type of object to allocate/deallocate.
T must have a non-throwing destructor.

<b>UserAllocator</b>
Defines the allocator that the underlying Pool will use to allocate memory from the system.
See <a href="boost_pool/pool/pooling.html#boost_pool.pool.pooling.user_allocator">User Allocators</a> for details.

Class object_pool is a template class
that can be used for fast and efficient memory allocation of objects.
It also provides automatic destruction of non-deallocated objects.

When the object pool is destroyed, then the destructor for type T
is called for each allocated T that has not yet been deallocated. O(N).

Whenever an object of type ObjectPool needs memory from the system,
it will request it from its UserAllocator template parameter.
The amount requested is determined using a doubling algorithm;
that is, each time more system memory is allocated,
the amount of system memory requested is doubled.
Users may control the doubling algorithm by the parameters passed
to the object_pool's constructor.
*/

template <typename T, typename UserAllocator>
class object_pool: protected pool<UserAllocator>
{ //!
  public:
    typedef T element_type; //!< ElementType
    typedef UserAllocator user_allocator; //!<
    typedef typename pool<UserAllocator>::size_type size_type; //!<   pool<UserAllocator>::size_type
    typedef typename pool<UserAllocator>::difference_type difference_type; //!< pool<UserAllocator>::difference_type

  protected:
    //! \return The underlying boost:: \ref pool storage used by *this.
    pool<UserAllocator> & store()
    { 
      return *this;
    }
    //! \return The underlying boost:: \ref pool storage used by *this.
    const pool<UserAllocator> & store() const
    { 
      return *this;
    }

    // for the sake of code readability :)
    static void * & nextof(void * const ptr)
    { //! \returns The next memory block after ptr (for the sake of code readability :)
      return *(static_cast<void **>(ptr));
    }

  public:
    explicit object_pool(const size_type arg_next_size = 32, const size_type arg_max_size = 0)
    :
    pool<UserAllocator>(sizeof(T), arg_next_size, arg_max_size)
    { //! Constructs a new (empty by default) ObjectPool.
      //! \param next_size Number of chunks to request from the system the next time that object needs to allocate system memory (default 32).
      //! \pre next_size != 0.
      //! \param max_size Maximum number of chunks to ever request from the system - this puts a cap on the doubling algorithm
      //! used by the underlying pool.
    }

    ~object_pool();

    // Returns 0 if out-of-memory.
    element_type * malloc BOOST_PREVENT_MACRO_SUBSTITUTION()
    { //! Allocates memory that can hold one object of type ElementType.
      //!
      //! If out of memory, returns 0. 
      //!
      //! Amortized O(1).
      return static_cast<element_type *>(store().ordered_malloc());
    }
    void free BOOST_PREVENT_MACRO_SUBSTITUTION(element_type * const chunk)
    { //! De-Allocates memory that holds a chunk of type ElementType.
      //!
      //!  Note that p may not be 0.\n
      //!
      //! Note that the destructor for p is not called. O(N).
      store().ordered_free(chunk);
    }
    bool is_from(element_type * const chunk) const
    { /*! \returns true  if chunk was allocated from *this or
      may be returned as the result of a future allocation from *this.

      Returns false if chunk was allocated from some other pool or
      may be returned as the result of a future allocation from some other pool.

      Otherwise, the return value is meaningless.

      \note This function may NOT be used to reliably test random pointer values!
    */
      return store().is_from(chunk);
    }

    element_type * construct()
    { //! \returns A pointer to an object of type T, allocated in memory from the underlying pool
      //! and default constructed.  The returned objected can be freed by a call to \ref destroy.
      //! Otherwise the returned object will be automatically destroyed when *this is destroyed.
      element_type * const ret = (malloc)();
      if (ret == 0)
        return ret;
      try { new (ret) element_type(); }
      catch (...) { (free)(ret); throw; }
      return ret;
    }


#if defined(BOOST_DOXYGEN)
    template <class Arg1, ... class ArgN>
    element_type * construct(Arg1&, ... ArgN&)
    {
       //! \returns A pointer to an object of type T, allocated in memory from the underlying pool
       //! and constructed from arguments Arg1 to ArgN.  The returned objected can be freed by a call to \ref destroy.
       //! Otherwise the returned object will be automatically destroyed when *this is destroyed.
       //!
       //! \note Since the number and type of arguments to this function is totally arbitrary, a simple system has been 
       //! set up to automatically generate template construct functions. This system is based on the macro preprocessor 
       //! m4, which is standard on UNIX systems and also available for Win32 systems.\n\n
       //! detail/pool_construct.m4, when run with m4, will create the file detail/pool_construct.ipp, which only defines 
       //! the construct functions for the proper number of arguments. The number of arguments may be passed into the 
       //! file as an m4 macro, NumberOfArguments; if not provided, it will default to 3.\n\n
       //! For each different number of arguments (1 to NumberOfArguments), a template function is generated. There 
       //! are the same number of template parameters as there are arguments, and each argument's type is a reference 
       //! to that (possibly cv-qualified) template argument. Each possible permutation of the cv-qualifications is also generated.\n\n
       //! Because each permutation is generated for each possible number of arguments, the included file size grows 
       //! exponentially in terms of the number of constructor arguments, not linearly. For the sake of rational 
       //! compile times, only use as many arguments as you need.\n\n
       //! detail/pool_construct.bat and detail/pool_construct.sh are also provided to call m4, defining NumberOfArguments 
       //! to be their command-line parameter. See these files for more details.
    }
#else
// Include automatically-generated file for family of template construct() functions.
// Copy .inc renamed .ipp to conform to Doxygen include filename expectations, PAB 12 Jan 11.
// But still get Doxygen warning:
// I:/boost-sandbox/guild/pool/boost/pool/object_pool.hpp:82:
// Warning: include file boost/pool/detail/pool_construct.ipp
// not found, perhaps you forgot to add its directory to INCLUDE_PATH?
// But the file IS found and referenced OK, but cannot view code.
// This seems because not at the head of the file
// But if moved this up, Doxygen is happy, but of course it won't compile,
// because the many constructors *must* go here.

#ifndef BOOST_NO_TEMPLATE_CV_REF_OVERLOADS
#   include <boost/pool/detail/pool_construct.ipp>
#else
#   include <boost/pool/detail/pool_construct_simple.ipp>
#endif
#endif
    void destroy(element_type * const chunk)
    { //! Destroys an object allocated with \ref construct. 
      //!
      //! Equivalent to:
      //!
      //! p->~ElementType(); this->free(p);
      //!
      //! \pre p must have been previously allocated from *this via a call to \ref construct.
      chunk->~T();
      (free)(chunk);
    }

    size_type get_next_size() const
    { //! \returns The number of chunks that will be allocated next time we run out of memory.
      return store().get_next_size();
    }
    void set_next_size(const size_type x)
    { //! Set a new number of chunks to allocate the next time we run out of memory.
      //! \param x wanted next_size (must not be zero).
      store().set_next_size(x);
    }
};

template <typename T, typename UserAllocator>
object_pool<T, UserAllocator>::~object_pool()
{
#ifndef BOOST_POOL_VALGRIND
  // handle trivial case of invalid list.
  if (!this->list.valid())
    return;

  details::PODptr<size_type> iter = this->list;
  details::PODptr<size_type> next = iter;

  // Start 'freed_iter' at beginning of free list
  void * freed_iter = this->first;

  const size_type partition_size = this->alloc_size();

  do
  {
    // increment next
    next = next.next();

    // delete all contained objects that aren't freed.

    // Iterate 'i' through all chunks in the memory block.
    for (char * i = iter.begin(); i != iter.end(); i += partition_size)
    {
      // If this chunk is free,
      if (i == freed_iter)
      {
        // Increment freed_iter to point to next in free list.
        freed_iter = nextof(freed_iter);

        // Continue searching chunks in the memory block.
        continue;
      }

      // This chunk is not free (allocated), so call its destructor,
      static_cast<T *>(static_cast<void *>(i))->~T();
      // and continue searching chunks in the memory block.
    }

    // free storage.
    (UserAllocator::free)(iter.begin());

    // increment iter.
    iter = next;
  } while (iter.valid());

  // Make the block list empty so that the inherited destructor doesn't try to
  // free it again.
  this->list.invalidate();
#else
   // destruct all used elements:
   for(std::set<void*>::iterator pos = this->used_list.begin(); pos != this->used_list.end(); ++pos)
   {
      static_cast<T*>(*pos)->~T();
   }
   // base class will actually free the memory...
#endif
}

} // namespace boost

// The following code might be put into some Boost.Config header in a later revision
#ifdef BOOST_BORLANDC
# pragma option pop
#endif

#endif

/* object_pool.hpp
m+YdTV4b3xktPovIHa3z+W98vJhvmNsvCAn+OLqZJiHaooNZLOHJ704WNsUZUGmNH35snALE3wmw8YsChXlQ05FPGQDfiXNBhcfwRddDjCHSyfDEQ0olt/3ycL5Y1ZwHR/GZWYUeNeNZVbV5gR4nZeVf0sA9HyZomHePFfVONHdHCNAYezZmID2S5PGOA3x5kL442mOQP07yHQMcvlOTRw43rJwyDMQ9UuIbPxizEggzuQUzkiNyfKAS7/LFUFYMJy1F5HmN15qhhr+FvGY39wwnMZnFnVWFW1SYXb4hB/HYe5aVe04G0pRn40cJj2TxTlasTTIfbvls6gwh91FDkRkcjEA3zfEDx8aD76c5Ql4zT+5nuWD2cojvp3ihts6NeW7wxPfbkSFWTVdA9JjleGLvJ8wtsFqzn0/5/3s/96ZH1COHt432nImZ2Xj6v81thHEEh3nU1G16WoaRuQmXmdl5ejqu48n3z/P2Bm+bj/eK+X4f95wyVS9VatO7pqe1ROmvtmWiW//F9QaJFCmYovSWFw+ZJZbzPVPE8IJvOMYsSLWa1bW8j7OFk/WYk9LPSkdqb39mkRxi9ikc6e4VWr9ExzeqV++jdmArOObNnQ82uMdUsXw0ZVofiXPA/h7ObsQb0e2U2t35RhkK/U9E9mEEfSSDAHYYoXg27TuZgLxQhZDN/QolqxQrM2nzdm4ZRktrVPDkF9L3xITX1kwkpNe+u8qTXHJi3SZr3u9fFbclLqMBaos+latXVF3tbgK9zvTLXME3FwmzKnRnUXNf2b/PW0Hcg1Esqn8ANUaMujVXQNlGACsvQH0sCbQbO+TgnrqTT2epdAqB7CWfVz4Wk+6HGkjAiQi6swqbRhMDer29kWnzfQHx31/YqKTCziL687kxeewoNT6kHVOJZczG5g49GzHRTb/aH7ajP+qgnUK7zUzfSjTG5t327DL/hsdCNcdEkigsrpFBJtfyi0SPpIlpdg9o+JRBzp8z5Y55G0QxOpBt1xiVOe6k89jD9T6nwsve+/9xMZ78aT2lZNAk400X81eDn8y+aIVjeRNjkmFKZOsQKjK1fpBeO4613hrMWdhKsIpunfCnC+1hTQfFVM+1URVJp8w9ZdlJD6+h5aj5NR7W+TlCSvxsVQ1f2YpKnbbW/dGIqxObl2RpK5mtbvmPnd8FfdtEYeU1OnIMXn84yAXEJzbbIY9akD8mV1peXiXWMCsT/7jrRqiBeSfuIrRlnOIec9zATiBatq2vkh9mhrI+lJ1Hf5tfhl9ka2YMhXn3g+WCWxyFcNg/Uh7X22LfSK7waUpMv1XIVf64yxw11X2cyquxHkVaBn/0oQkNvcqd1BF2MpR+GTZTdzVMcTXM5D7fbX4w6lHY4eD70UipKYGtgOqnbyiTsi1Jvgh89zfX2Ft5J4Vsudc4dHw6uwt/jMmq9vrAq2V7BmPdSbeXDA6rIc+WnKT2O+cv7g45BaEhb+1BMjCqMlmknjyV46fztkpPCgyD0OIVf2pmYbsZMJ9Ku2z5f29IaWierwumjmVHYi/r1xUt85q/Bq34KoGyNJ5ToCZzXXmqV3Gl/e2I6zVLunbHCyCldwuIXYzA3Aq+ELUlnzeRxm+8bZaO6LxStDE+v7HvR2aEwkxpF79euMCn/EUh20nZR+iMmIgng1d3hHmOu029mWdkTbo/mxlAX+44Y4qWQLLtMv285MctnafEkBYZsI9nm3xqb/vrzonKu9TUnvGtQ3vzjmobsjrXozfEfMd+XLZ+h+0qF9XRBEdilaZO1PX6zUpHp+z1lYE1uxMlhhfzi2eOdr1tEHT2lVw6aA1hGIdO86hFyrfONf04+i75Xa7p0+/Q4ft6CctQznWCtT41w5vfWf6ZvxNbt/JS0iuG5G73lo2JOa/fe1/Fib4x/+LOXmAcnGdUcKz4kkq0Ur/vqDJ6l/iAfbSmqXNRryZgy3rKzawcfVcbi6HQMf5U665YNx7yHvl/sgv9hTwnxf/wqhoCudUVkd9zKZrLaCqt7Wtp5z6dKbbB9oryyoW977oOSzylmPryStWKpyttph/HUVQpqS8LFR8lxbI/5/FexO5cHN/+cSSmMFZQlSHHkDxniDvTH1/ZSiCJwgKkZVGksYGVhyHjZUJcz3ypxGp6K6+RxfZzY3gOpFaVIM3hd2wCXklV9QevJCOpY9X1QRc1SwI8NnqT9P48UJk3yxg0w77d8W+3x5V7S5y+KQ958EPpNR09fF5gvcpDQuSxokBiCCvA2LISEO93g0F0ey2dASb4E+0q+rinKJhwYUS+o2apiFBwlRHS8/7cvINdrQGqkrzNYjl1jzlbBYd5DXW/86tR7UfEkHWSla/F5ClJl2zHPvMjGD1Aj2zaxkSxb7vrYeAZpO5nabpbspJTrMG1A/ZjQJhdCGOZt3K8SUTGmG3sp099ID2gjUTRIZSyVOUwYyPif3aKTrBTIixXX23yT6B/jOGTP3d8a2/aXPb5Hd1lUw5yna4zc72KxMoBqgfsLUl+GMciYkf2bSjxhZZXe25kZryGgNzGqN2RcgYOZND/MYVYIccCOZFHbH5DTqNTtDi9xdtAfuWwsbGyj+Jp0CR1x5AKEyPsjmVTJJf9Ga8JK5Ot/EYo0PJIOx+PWB6i9l3jB1tAyJcXcNSh4rJWpfxnB8eXDXCSrYXB7y63er4MAef/mtPwj2JTunxlmUtTO+fDBHEMbq0pc4AWR9R92AxOBfVqlqf0r/kn/BiPrukrXxklgDOLsVTkcPFAYWADviJ9KGOqtYzQh7BLFqIpn86af4T7kDdzKJbHigYfY0k0UxUrTZPz9juGRl1UsVsU/WscXSet6vJdSW4ZdLaaYkF1U4gqA+UQViCCBVuwxQvGWyQqZbUwA31GY9DyXWR2gX83NQzj5ZFrOVXqBnMvJYJeiAWHnV1cwpMAxubLnRRb2thwC7dlFanfAuOtxrp71lLuO5b5BccWo3NKXOY6+md8Lqdd1WBJygkMSk7oYssLTj65EfOohUJx5ISbNcLnTYQIT5YUL/nTdK/UUmWLT4Q6ea1xNl3w4TTAP3aU544Fn93aLz+XVurU4J0xhIRxBSIgtAYr3TmO0Vnsm2o+eRKvVrW5lPe4udTN6iLYWGcV6YRs9eCsvX0OPHJxxJZvLKzuIhqFtO7ryNEoWtJimmk5nXXzzN0gXyM5ZU+ZG2c3X6ENs5AHhWBjatPwQOO6Zbl2ZUzOo/7uXn0v+idaCOo4tDtPtx6lH5L2I7c5Hg0jekp0T0o2NWMFK0SGAOt/5OpnBKnCQi5rvxNqP8KUFrOrndMY9nlYPsFryl/r8YUHQWv/VvoFiZVYSxwQsz94XD8O/XZTjn67MsB8a/zYJNOYQI9QfnFbR45bhbZr4H74Ds0kx5R6o6weV4cmJhfl59WJGnYttXsRmt0Gf0a+8dqEk9dwbDw2q0X8ywrSiTU6EBQ9aGTt+Vn4TCZckz5/vn7V9Up7wdScK5ha7PGVOpM4TJKjjfpkpwzetwUHPpDlEw6qz9f3SbDoIhKNlAAQLiEhk9YoyfeGKzLWTSuV6acPp8p6SsIt+Wdy6R081UVJokrZm6RS9x0afMWqE/Vjf1dNH20wqT9AZwX+IQ/9x+gRJJ6k2eVfiHHWRj2yF+QGIGmzCiZ7Fn0R95kVXURkJWxr2DDimaJBmX7Gb3EYvRgxSlJd2Iq0QZcYgeYBLamzRQFykY4tGtyezg/uqJ8E7piPl+q495nqWPeaYrqbv7/eyfOtyh4qcvfWZJyvT+6oT4j1SuNmiw8JZoN1rH70K4RwLOicH97Z95tXNLU0XNm8gLzwjH/3mTYTOebzs7ZBD4px87AZF/1HJHtJQjDuVv4R7GJ0vVHo0UNUWgPchUVeaXAY4qCRzn3dmvJ8AbvpTa3v/2rpwXbDD7Mwy2YXeBXl5bmUvaO6H+cAAr3koxmFh313B3QLo7xs7Jd11Jqngi4ri9L1zvejX72o06wTPbMoU0Mz/C/3rG7OdM1HrFLuuv7lJWjRv7XdajFvkxkJdbe+fRg/G77TAaZSKMGQwfG7tl1l6xrnVt1p39TBAyYOLy8J0EsbbkDWWWYHsCrEEfD7KqfLlgrffRiE7hslC+bv5YyGZaITuD7VJaTH7EGmxN9zqdjh/pYd39bClsbEjL0dXyUQ6ugOFo1N5dUSsyvzWFTNnxp0NHW/waXU8UlO51Y4+ccWPO7SXpiNW+HUHszoX3EO5R9byBnB2Dl/xg8oBXkwcvESdzN0ZMYPLZpgXuZykk/TM79qpXPERPcE7QvVsSlGq6z1QGPp6GYex6WxEYwF5OjpFZXL34MGVP5jA48GIhVnicZ8Qqa72fQfWzq6H8/t1C/cEkjQKRO6jPWv/RzG8t8XyG9VeQ+2pf/HuvlT4trr/1/nJ6+D/ffe97phQhWWJYn8Ip/m0cLbJQMHGGzpQkgo6l/hJIEwUkZl9EW8P/+SpVbSpcRqvVxU+VsmjMF/XQMxLdg/ASx1fFjiBFrxOvAb0JSUZFR+3JRlqO/Pa0dH98KlWeHBxx/plq1mec/gR/F16/T9WOvZdpCMkJHzwyGg2LaZNl1JRlzmdgecxom5naFZtR/4fGJgalvaUvn0tdHc7JmM7ey2ZlqWzqWAI1YH0QOKle6vj5ZfOLHqXO3lU0m4eC/W2nXVey3jEVdA2bXkzViyVH6ZArNxayM8Shu0YbcZ/bnirSXh8xJQe1HPq2MH+nqprTRynFL1AriEBcJDXh2BfDCVDmxhIOw4RF9eEQPiCTtZ4EdRvfcrx7RPT54OZKfYUQMK3i7PNhKgt7u7HAIDktbvy9DHooJgD8efMePtjpG8fAfVqerNfP9wllGDApmjNL66zxwGe6AsVIyQv8dOt9CUvWzefBbiEW7Fn+7PnYmYcq8GoGFQZqk2cJd6SYKoq4pfnbEJXc7KsUlu43h+ulmWdZSWS5KfDuVgYV5zFOF8qhPeyLOAF3ML4YSu2etb6LJTh3N8EdI8CF4HtnP1R3E9XHomQjzcXxMpHTBU56mU/5mmX29lRv3wmYCGE7oXFpxpnw1Ve23Zu7gtBLP58n2znHPXcXzXeAW0dXOJ5ToYfZOG9ntSU+uJmllh6UzfsJAO3UJIFY+kYX1QwoBeVT52dGq5bhTLZKGput6guAzJH2QrGgu0D5zrRwdMTU3yVinTZ32WlduH+S1TM5J0LRSZG9GMRlaR2aHB1HcVeQfhADIwzUa+w30kBOewSEdUJrhcGcZN3kiG0RjAPr+dQMWEP0n2URGj4UC4iFtu+Dvu1dOklU1Pntpt7nne+tPRkNO/vKhxVB1nAAIs/dPX8cKtRdpvwUla4Kex2KAtMX3zhGP+G/FMghr0nMPG0y4DLUSnAYtTSlvN4+vqzGFt+A/2wZO0RbUFBY7DwU+QW9lwHW3JgrVyfjE+rG/t8Qk9/JbyxouHemQfwUbqUcF8WR3GpV5iUdxRDa7sY/xnKxjUXzE0OdUWn52UIjPQjFgUF2YISwg3pFmJhtJKLDbf5LCuL3Z9ycoL5mSV+2YDJhNdlqgVSwoRe59bsnyrnyto++uhPMLMpJ//zQlVoj9R/JcgAGxr6hAMWRr934yJQZrAKul+EAkvAA3P4PykZaFb851j5s3LVsmYzYAkoBQL7erzwAV+2v0px/k2T3tCp27Y9u0sPKLq3EME6YGTxkFLnDa0WjlL/X3bw7ChGD6xcErZpTZAIgJ2HDrYLs8enT626D8fWQU0y3T8qYSIKTA5Kp3x5fZfiD9W46oEghFMFd4HKVs0BKnDHgJXQU0HKzHydiI1kn90/ThEgF5p88UlLclZ7Mtuyd4ECF0IOQLQCi4jFQzAlx9ESqUv2QTXtm/d9TqHbY+MA5O1xAptpxhatereBircoIYFZ+SebSlH9iLwVWJFRIweJbtEQfzs3bYdr2A5PYg31psKvw4oTAFGAroJi5IM+tbdX+y7FXjsvr5MEt8Y/qsCGt/0x08+dwXUyUX2wa9iDLYdJfOjOLwe0hIwrBttv0mrqnHGJ0bRcpoo8osTfLxem+C02nmGENS1Zz6ekVSCBmNbOnhh9ekmpp4+vLT5riWAjjn9kWKqeLn34EsDTh6d+DiTr1Ka/IRyImLPhRE0gsCDPh/1icr+9+ngYNippMllgaHqY27zQobZmxdqO8mondn1Ju0HLbkWZZkwVzqesh7vnUOOGvW8TnKxcuO5ssKOOJ4wIIccSBjg5LO7pAJQ1qjpkKKQs9zZ+jcp/OnXaF5ow8SizCDlPm8vkjsbq1E5P1YqVyvW9IOxaBhtRnrOSawHJjcJd6yKFOsuJJUD4V+0acYJYcrclufZQEgTMEAeaKIKTSPrZEYWpMcSoljvnuO9jGWhjZrR3VamxctQ0APq16NfTwF41MUdVtYo/OKn+LN1khCeRqwXk+1rE1zlSq0uFAmTvDCOiLlZQ8SFUZQfESPOfwHV/SxnVQAAfV53/nLGsIWboGsmb2JBhKzEjccoqtM+JECiqrFSgmUd6yYeuhB8W9guhYU8SCzzFpylGpWd+cyv73hiKmSLwjS0OON+mdFQT6famz0xsFCo4CP8Lh4xTikZOoe/LP6Dz1chAU4D+ijY/DlFHa+WuuTkAgRP9jKhVLuRLZRseYJY9jXRNx5ZAw786vK73bNEmvZfvfLPARojWDkD4sTFBrWsPXuEKjFzQfqTn2NZYxTFMlCz3HauDA8wI0y32Ban4KkqkRjhFCu1ookkt0R8S68jGJUsIMYJKAx+h7tE7W+7l6qNH5cdUgVpzshz948rGvYyDItZbYPJA5TGnv4D4cjXI9cD67Y7RzeHRfsp8nLsaXDHH/um17c/eM9Nicdz+QGHoaL96ImXdrsFuZjx92PsRem+lxPdsHtVwaood7j3oZExBUmiAVyJ6grWQQkzHFLyY0QCPnEqK24yI6ujd3Hy5K5Y9jq0lPNpicIYJO0gxMxjQLp2oEeW0ip6VG4q9keUKECkRXCMCcgyZpLqM2DbTRRpR6RMweMTNthuaGMnCmPXZ0uLxM2K6IoA+q7s0mrSHj8lB5fkEi5anSwimhJjpWC92bO0RaQdPF0kwOhL9C0LZw9vR005REOMYE0EdC0BAoKACmSS9lJVEHcc2m7aqr2zE347h6dbLD+Hb2dbXwBI7rdHpgsqyAOOTiD0b/P6dVVnF7WOK3N9VSFYvvZxNrSx9T0thbE4XHWNviMde4XeDZaT5xTxa/+4/749u5hbGV+/hV8ZegvLSk83P+I8vzdfTt95mtAbR/ckjlQ5gGDZyfoGZU2CW0IWhlbonyfm2Kpfy82Ir7YAPQuBsgGfJFZlcAcn4ANXPmsXqp96AU6JfPzYD4uy1nOWRO57qrax3UUsDVUyKio95RK8imv3N21xCy965z4M8063ZmdPn4D1d6KW1TLKIcAsn592gTXbBsNe3JnwJFrXloCuPVSnWNengXeNOPX97Md4b5NkV+bk6uHuZfKkvnina7bPF+53I+JuEn3gQ8fckv2UBMw/qvdc9KbomBRHZhhqw6tz0/2Au9fTVTRE+oqu4zkvUenTQLTMIaYzCLstyvc733i7U38A0j+CThtz2m4o+RT44yO/M3X0Qf12sz4c4zFuwp8w
*/