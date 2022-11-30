#ifndef DATE_TIME_C_TIME_HPP___
#define DATE_TIME_C_TIME_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


/*! @file c_time.hpp
  Provide workarounds related to the ctime header
*/

#include <ctime>
#include <string> // to be able to convert from string literals to exceptions
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>

//Work around libraries that don't put time_t and time in namespace std
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::time_t; using ::time; using ::localtime;
                using ::tm;  using ::gmtime; }
#endif // BOOST_NO_STDC_NAMESPACE

//The following is used to support high precision time clocks
#ifdef BOOST_HAS_GETTIMEOFDAY
#include <sys/time.h>
#endif

#ifdef BOOST_HAS_FTIME
#include <time.h>
#endif

namespace boost {
namespace date_time {
  //! Provides a uniform interface to some 'ctime' functions
  /*! Provides a uniform interface to some ctime functions and
   * their '_r' counterparts. The '_r' functions require a pointer to a
   * user created std::tm struct whereas the regular functions use a
   * staticly created struct and return a pointer to that. These wrapper
   * functions require the user to create a std::tm struct and send in a
   * pointer to it. This struct may be used to store the resulting time.
   * The returned pointer may or may not point to this struct, however,
   * it will point to the result of the corresponding function.
   * All functions do proper checking of the C function results and throw
   * exceptions on error. Therefore the functions will never return NULL.
   */
  struct c_time {
    public:
#if defined(BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS)
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* localtime(const std::time_t* t, std::tm* result)
      {
        // localtime_r() not in namespace std???
#if defined(__VMS) && __INITIAL_POINTER_SIZE == 64
        std::tm tmp;
        if(!localtime_r(t,&tmp))
            result = 0;
        else
            *result = tmp;
#else
        result = localtime_r(t, result);
#endif
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to local time"));
        return result;
      }
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* gmtime(const std::time_t* t, std::tm* result)
      {
        // gmtime_r() not in namespace std???
#if defined(__VMS) && __INITIAL_POINTER_SIZE == 64
        std::tm tmp;
        if(!gmtime_r(t,&tmp))
          result = 0;
        else
          *result = tmp;
#else
        result = gmtime_r(t, result);
#endif
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to UTC time"));
        return result;
      }
#else // BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS

#if defined(__clang__) // Clang has to be checked before MSVC
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif (defined(_MSC_VER) && (_MSC_VER >= 1400))
#pragma warning(push) // preserve warning settings
#pragma warning(disable : 4996) // disable depricated localtime/gmtime warning on vc8
#endif
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* localtime(const std::time_t* t, std::tm* result)
      {
        result = std::localtime(t);
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to local time"));
        return result;
      }
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* gmtime(const std::time_t* t, std::tm* result)
      {
        result = std::gmtime(t);
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to UTC time"));
        return result;
      }
#if defined(__clang__) // Clang has to be checked before MSVC
#pragma clang diagnostic pop
#elif (defined(_MSC_VER) && (_MSC_VER >= 1400))
#pragma warning(pop) // restore warnings to previous state
#endif

#endif // BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS
  };
}} // namespaces

#endif // DATE_TIME_C_TIME_HPP___

/* c_time.hpp
a8PN83XH3oO0zanzR0z2JSZEPS6uo0J+cHk2AfG00/mtIIvx+RttjFlNnySaCTcdvbOR2O7WX9U5bzhgSeZOuErSC9W6sMsbQMRAI7eS0sYmiVk0Mfpz94ZBxI28BLFXcWagcl0/lUzUDhw8z7ix6M8SbSaHRHc6+u0rhfnS2TS1NG22YmBsrYDwu6b5r+6wAfMM1ZK0MH1KXaEoMoZrhnj8DqI2io/VSz3dObjLTxiFbYzKSo1aPtN/4z/Y5uvkegI6s0pYc69nlM0v+nLEWA4Z6dRTcHEN8sCUftyX+EuOhvXcQkWTh5EnPPc/weq8VclPD24AaL0JyR+udq5ECfnOS/MaaJ7NWxyyTzvo+NN/T68kllsv37XcfODCMOADvKKQ/tbtY6+/vEve79htt+5yusetWlO+q0Ihs8M06zhcBa15s60TWSRpgb8H14hRHORzXW4lHZGxacmbbYKkR1l0XkqSvwy6s7pOItMieTYocpc0bfbbcLJs0D++MiUSf34Mqx3aEtO4zSXGOi+A2pOeg44acVBQil1Vy5UrzmGm8HHa5DHPt7rUtWJAsvusAixbyHKdApB5dp3PwYKG4gJhjr9R2EhcYgcJLFtkyN/sCClYREGEfhCtwN+6MPYspG2CtGNLR0Q1eR/p/4lJVniCTijixb2ZWgJ8oMcHrUdtMuY+7RDMcMhANu+KinWKCPUj6YsW8rWvMxLRIUhw9yyDQu2hWJkjQtivacwp5cx7VcWvEtIAK9A1KlVXQvRdSZrsIwPohiFQ+7KuesqyB28U7nBWLEyKDxDCM6LEGm+S2num8FzBCPdtZv6BLre1j6amlESTtF9/b7H06IqhauJL87RYYdSZIC3FBZSPJax/iXEDGIJZT6kJ3X3Gv+SYrzzR8pEFKXDevDHxw8qSERYMYXcJ7vFJ1dxlKbkiq6GljKF72s1JM6w7j66/wemWYku69RzgaKsOgD0cJoNoHQ6AWfsxB3/2oFxJysp5bz0GEJH9y9mqnkTvFe5SSpnG8nz/oG9xo68gBjsJp+A+t187DyjB4OAMJtXqOMsvxRVBKrB7rPNTuQIzMckBduWCjhj5cR5asFCUzG/GWIMqMVQKo/OjhCtro+3ciJkpaOcYJGVm7XwE14L9/jmNcYKJzfOu2AYocNBoScWsqEkUFQY46qV2cSWLIEm/WelD9MiovyUyigyrxVIzMvhGEHD0kst4CjGGwKwfu1dv4LBva9gzrkRd9S3ncABVU6BQFm8N7cbpGq8wxoklvE2PBheKp2Bz1vJOphG1edVJ0bU/xbcCXLcA2aUEnqMf4rpiq0mCVQCb59oKOBxPyHla4HMiLg9LOchdmNwJUdplqLJx49NI85i0NLQvbcKjmiFBmZ8ED5dE9dISmFPtcd0rTCBNyVO4mtGLVR5SaGnWB8yJq/xIxbgJQtV7mcKpU/upfaArPTpx/Ow/+yr1vzp/0R+OEw8IN8UcElzQ5BGIAWf36qqMuqOtct5Xuy2vl+0V2Cz8xVA04a3E9rn4tVv2B8L0sj9C9G9hudjQvlA0+nu2xWnkbJQuqAzX5RFf9IsZK3P0Vv+KJGfh/qRjSrabk1qAyodoYq7ZlKyRbac+2CslXuuouOpFV7ZfFoQQdpYXWBhd/O0ONWIT92CC1k4zt7E3mvDg76kf7C4ESLap9BbbjwCZRVz1ij1oTKTthG3zMzvsMLQysL1AnYVUqg6od2/RlcDArAsLbBUmNdtSFHpF3UpsboAhyoMAJPET3f4K7iCbfEBftvjI7ITAR4iKWTG5uJRuRO/KnJxGAy4hoCLWWG1E9ErR9NUCg1T8COrFafMlkWLd2fQrmAm5uKaLFhdve/4hhW3xhLRoCZcDjDU3UrA01PYpPFyLaY2kYKaYwJ3iVxrSJI4Kq7zybjiinuPQmUG6Ug/H8oIAa+FVxo9ZQrIqkZdxX6EgrzkkpbxwBWPuypmAmZ6OsbyZq9+DN4X1uiPALi/X4TloUSXdAbYyi8ttBm1Y2crqTJDNzmN265yuI2XWiC4wKemtJgpbyIt4YL+nV72vmgc924tiwJnik9jHt5RFyeT39PzML0jHAM3FMs1v0Px5bbW8LIWC0If3LXsdTocUZcloO6dhGFTkK9PpKnwjDQMzWgm4hfUGnfcQlfUaDSChdjyVrXUFIxDN36lp2Zslkpa3NTVVS/e7c2/hSDVXZiNK8kfjxPw6qS8VJnaUrWOYDcCnolUncBL9xohr/wYVgDrK6wlmpG0hC27IU/vAtIX9BxB8lzmfo8cSSoF/Lfeg6NTk7qSMPNjfGl+XcvFhRHWXUKKRLNxTcDBcjADQGn9t27Zt219t27Zt27Zt27Ztt9vd2YeT1zt5SW5mMrEsyzs5xA6OsiVP92LRghhddaAZDF2HOQVMitqwc1ih/1z4ol2JhcQyjQxgtGRWMz2b+jzmZ+9SwG2yBx2BnOqYKFcNJ0qd8V4igKBAJLvvk70Jpa2bXmKZs+SVuXENVdQ7t5GNxRpJ/bLjmst2a0ewDI0X1Voxi9lWHOly3reXCfM0UH3eEtZj0LWENTzUPjxOjQk4JfegTv3MV0uLOQvIDkGOqHRwqnqetkfKzldcuLWIwaDFpG0nMLxJt5gZaIWZ6SQJqS1Au4wCMM1qVt8GRNL5/VmheUUGR46Y6/cpMkTrriW5esMf8s5O6j12tlzypBA4XT39fZOieHdu29XkO5e7kHaHxqGuxDAvJDvq/ezvfZ/PtYUEGxBZieAbkP8qhJkjUJ84FIMAGQDJWjSz/NIvscgtnav2zUHERi7zXz8tv2f4DXfofDmgP2Tn5AyBMa6nyejrpBOLK6F+5Ajr5YIAVeA9CjpIlJ7wzdSA5itrhtUOD6v8OR4ioY54DyuBFTLlvfqd0IgE0g49kdvORLDyn4BYBby50lSTtvZxEQyaCQO0in5pR15kRF3P9Uq8iQCBRXpuDzEGBkSONIF567ghG7QYFFG8071rR100wMe4xza4HSL2eoxxaQxYBj6Ru7iIIN9QH/ehHyKWZmt5m1zBeir9pCCtX8F9jS2JsuUQCblzyVXuvXiU8X1B5Z4EXKJozpQzYn0KcjoAP10cn+F8oDg/YR+qmYEUcYWmd67UJb3P0DiilHOA1ESOt8PejGK4umoBcW4iPWdN2zCYXIWM7tVMDJDxh8n8NlH9YPnOGaDFIan0xQAlGVJggs3OpO5KIgtOe1PFH5DCOX8TrC08Izl2ZGPJBobYdQV3gFHGZyUZryzd3aOeb00S6C/72mzU0oeSX1E7KghhGSqoolq3wL3oqtOkiAtkaoE2vjtwtfgQJuSV8S0dWMflEwu1ikG5TpXiF1Mzkq+/OiqsZ7ywgfwJsSzzNP1W7mWdo+Vhn4ZIcmaeCU7vjavww4+blUEPAlIeIz/flTp854c8mgn3zOxUMZg8fsRNKvPnbL/kDV8Qfku2n4aCr9xYANywNdgBEJq5an59EK1518UUz3PxfBjlfPaKf/fqEZzWGgTlOGAOGnBzbo1975Bb0BY6QiJyL9AXHBzFxPyZI1HbKjNTLbSNL/QwLt4R/aCySJW0tMRb82e0MNoZ0Mb6R37PhRVHC0hJvEqQAGM9sHbXfoYawyD0zxiaeAxWdOASwZS3H6OTzW40YGtTQPbSlyGzpVNmF8XNPNrushTPD/BcN3NZC1clud9Pq+qkkbi8zrnFKbQYZVaTqZq3E6nd8JExd43mqBLU2/jEsm2FO7hcJmfmoDu2SL4HpYekN7WnbykW7nYZvbstajz9RUw4qvsGBsKGBTENWcWHbE0jdoa2P79Zn4vkfZq/f8UOis/4ZjpLjLyUzah0ZL9SwVcmmC3a41JBOa59W+6DEyITA06EqSAr6kW/QRamss28VejAEqdTS4hEbrMsdmt0fgLN4e3rtvQxlHi6VLbKT8SI9SOcYOk6ta5WNGkG+zHrGIxtWc14nspWm3t8xwtldCpihl2xYvWRocsPn8iHceNB7KyWoj9ERLTETNV+HXG23jEqHlZPmwZ0CPmj6gJZ5cpkgwJegsmS9R91CBsnmqJcjn4O/gn/3HFqpKdKOFIRif+dccVPP78oPtvqbHU1bxe/BGB77OnUTJFywqj6FF5aocvDqrUA+nJA0nnfbTz1fD5CIi8ZiZsmU2URS2ti7nzRxgSJdWePFKlmYkzX5lT8+uRSJY9OSO8vRW1daUdKrHezJZ0GToua3fUJgKCweEgFt+lYv7UZnTEUEcmAUXXAHgkJncZ3WReI1mga/AeiUUttOATovoZR/lFML1Bh4YtgR63FnTB8fkrNTzrVo03iN2gIHoOQ30Y2tRXRAQzQ23bPf4DJUjpa/7GQ7b6UzzH8HtTanzGhtfk9YJKLW+hfJwumW9+y9U7H5rlBv/nACp01mFRvcadDO5jBNIdQN5fUdYFW8jsMrpyHoBC4LdXVFK64f19ObWzGG/XReH1COIKZcuWq+X05LN8DtbJMn2mJ5NEQewNe5WnyqQis0RNqWWa4gOprZvs5QzvTt9HCptjFg70SciC/r/QueBFe1l70uWpXD4awTHWSJPe6KOqiomehAa/8fGRR33O98KNoX+bVb3ifdEgmKG5dRJifsyOSwNPpPQkGPwQ135LKEK6/fYNLhQVsmvNhX1hhRSrYsWXLL/bI7+hTpZYwqQhf1pH4A7X6tF825yrgbUgpYBDlGK6d0lkJseYfOuioRMbPW2HdLkimNYhzc2yWiKNYx9UU3Cgqv3fM1olYxPnpKSjML2kMfUbY2DjJI1AfaplX0sbM0k5zVP2zYZOJo8GGeHqt5QEJHK90LyCdr2CKmdMIZ2L7lyaqTtbm4rIz2yCOvt8GrMRRcgZwEoYkd37lHVHAONBs+gLaSTLleedx1oS3bfLmn9jZ/h0zRl0A7xvf8OI3qyKtUUu+arPaTC2fXWxT0Qqv3aYf1izx31NcJ/kDyupdfGWXj4cqYKPvlNGHnAb0jGX3pI5OnEqp7mmONFgno74k34fjECic6ERerxTw6YIgnsamAsoYVHVMXY1JphqsrJDvtUQVxByAraz6xznZOqdV2dmoxZcmutVEaujwAsnmOand+i+vd8VOG8P6JNqSvrNKx3uSqBS42cq0DX2KpifDm6u8ElQK2n+7RsYSmeW7WlM3MfATD1C/yZgaeitoWhf+eqdgL5EdA0oygMZfV/FxeFxAMdmiXE3RlHX5z0jMbE9+SGKsrNcQdvLVl3Qtv8RTxwfgpUP9zdpnJUkRuQmyGyFCo1JXG2y2Hc5KY0vAJ9A3aLvkapCq//UTe2HqjHd/69haz1+GqXvUyDUZclSiO+rs32F4TyI0h2BYYiRuLNZjR8dlnz+vvss4R2FSl9s2LZGb4GZLnc98uabWd7x00CWg4jypIXs9qDlJVqK9tYR0k2wW1yZkuxoetOc4lLb0clwlWJ93NrdSulojai7ixKzz7Kvu6GbyDirumd6OxQf3PH8n/yA6IhrdoeihsWoGRrGxgRGYOL239SqUDw51MWIRJjXRfRqftjj0E3bCTtInJJ/06hsyOXVUSZIOyoHyclppXGtLWL1ysK39TJ4FGB+EyhhRDVg08J0qxXS60shZwNwYsocy7gqiVmGqhSOHPJlAWwv2rJbvEgqmpiDhiE3T7MuMsesCqV2kLBZ4WiAnQQx0I61qE8cTzaHYB6DqbExlIGZlI8GK6b3PwG6r14R3D/6GyuJW+uTA7uPb8wg14yBJ3Nrj1eKCn9rDyuD9nLuHeWpViqeoNYiIB+EaIZY9izc14Q4O/W78hI6tQHFTr6AUHR/t58J8ghtHeElzDbyPnGeS6H4ujvqoklAVmMnfUQ2QVap/H5MPvYy/c/iRkILKUccSZF2pzrlFV7WFa3+gS7LnGggvIH89c7/5zzaO7y+TOXp+hP2cQDbFjGBNQAhDJwmmlzBowJ9GsEZMSHHax+59pxzflUUY2qCxH3eCLWl5tkzDp6gspHzbXV9QjlS0ZGHBBIE/s+tWSQbB9mAFc5xRY2iSP0geno0v7PAGPOroH6ouAZdwVNuWjCoebHbWgqQEftKRenmbubmp2xphm+uv4+s9vfIOzaKwZpecCWVqgEBmCOYU/ONlYnOAxOuJFT6ZtzlWQNtCa8NpY+W/kZDsoN5pABIs7dMuVL958ev8Z9wD8RTrsbrRtmUrDyn25m+zkKAu0anmMR5KDXxW227g9pVdo/9jGMefbjT9XuaaPL0JXq2tXh1gdDWEFtG6lOm+KYcYZXOZ714eokyV8MKpedcwnHe/Vpfb0WzYWJ59ki7kyxvpW/9dQMbFTnTcKfRv7L9FSMfAXl1W99nsqqWzmubZZxgTIdXfF/8Q6qyXdZrD9wkbVfa4Oin6jvcPXm2uj8LYYh+z/IBah9HaaDf2jJ7iQl/j409r9aH0RMUKS5W9+YJPDhpgn8FaXIPiY22xun19v3gfFyLJulpNpRHoU2VvdjYS1J4I8hm3J+BgZGigz30R0wjkvs3/grbzPqmcR8qnPYJXEcyhU2ZGlg+yc9dcDv0G4PtPEbogfGzNg1Qmz5tNsepL6bo21Xk9MVf8TWeHCIYUhFAa0D6PX19WM9vVw5SZjSK7zpTA/8WORP/ju3BzRGtyHi5V/PS6cIu0a4UIjEtpptv5Vjux2+u5/Pnhbfxhe/E4/rfOFYAVoqujnKCPpnpxeebtMwxcMPTQPuFlFIRP1alwKpn8VhPq/JkgXSxgtB2uwu66eoOrals0boqjKOLr4mOpezjwUc8VvFwIv+N6Y1ngK+a+S5n1QZCWuYyBPdMHPo4bl+Zz4+RG+UH6+c8oMJL41uGoh3G6wldfyWY7yiNt3xMe07L28FYCGTSy+lCibtACSQsn2ktXnED9sGrglvAMFTb8JVnKY7lundpQvygUfcAiiymsPrkR5pCtc4oFE0N7JccivhthTPUdTKtA2z6is/WbyqOZrMIiweB7SqSLTGU/58m2Nl7LxYrqIazqoMrhaV52CEi7LbN/+dDzWiQ5c0hZbRMU3p0xMCQd/oeRyJNjMaaA9sNSzDgZ1aUHd7GPoJBiukKBf6+Jd8ZEFZ85AKnRLopNwqYo0ZsWCJlM5ibmfdMv7SjrXBB3GdmrdLuT5T2wZcYDN93qt9PHT+ZwZJdkoFPBziiv+0f0s5a4Pf0NFwYQNMi61zvTATLx0Duzc48L4M72dr2lLrxHc80W6D4oEr5dxTtltIPoGSenVk7HVmjBNcYNwSWTPVlahFRttZraluC2avPzpUu/+H2HprECp2fV+AQ8d0foyH3KU7vj945kqRN9tat2fGpo1/KUaYHD5DWQVXd3dTnhr+YGAeQeuBCKD6lO4qJEbpuoWtztwkTDOZA+ebRrTR7ycCLI+xXuhOjdas6I45nzK8JOGMAcDvFgS/hh0NBYsQCE9MndZm64JC6tiamVcJy47YaY6e7Jx2891NQ6hb42R9aa8o+RuX+M+v7KfX1+wX285v6+xf7F3sNcvgu+3q/Yj9naZyXu79nfaLqHp96L397fxp/H0d9i37CiX/tMtK9Y3x84m1fA6ENOpppHm4nNRMvVRHKwXX5M6dtzoanzSvxeAl3T3gqI0ZKFfMSUFOGHD3oekoEaU3C3
*/