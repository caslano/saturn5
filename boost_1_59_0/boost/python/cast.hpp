// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef CAST_DWA200269_HPP
# define CAST_DWA200269_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/detail/type_traits.hpp>

# include <boost/type.hpp>
# include <boost/python/base_type_traits.hpp>
# include <boost/python/detail/convertible.hpp>

namespace boost { namespace python { 

namespace detail
{
  template <class Source, class Target> inline Target* upcast_impl(Source*, Target*);
  
  template <class Source, class Target>
  inline Target* upcast(Source* p, yes_convertible, no_convertible, Target*)
  {
      return p;
  }

  template <class Source, class Target>
  inline Target* upcast(Source* p, no_convertible, no_convertible, Target*)
  {
      typedef typename base_type_traits<Source>::type base;
      
      return detail::upcast_impl((base*)p, (Target*)0);
  }

  template <bool is_same = true>
  struct upcaster
  {
      template <class T>
      static inline T* execute(T* x, T*) { return x; }
  };
  
  template <>
  struct upcaster<false>
  {
      template <class Source, class Target>
      static inline Target* execute(Source* x, Target*)
      {
          return detail::upcast(
              x, detail::convertible<Target*>::check(x)
              , detail::convertible<Source*>::check((Target*)0)
              , (Target*)0);
      }
  };


  template <class Target, class Source>
  inline Target* downcast(Source* p, yes_convertible)
  {
      return static_cast<Target*>(p);
  }

  template <class Target, class Source>
  inline Target* downcast(Source* p, no_convertible, boost::type<Target>* = 0)
  {
      typedef typename base_type_traits<Source>::type base;
      return (Target*)detail::downcast<base>(p, convertible<Source*>::check((base*)0));
  }

  template <class T>
  inline void assert_castable(boost::type<T>* = 0)
  {
      typedef char must_be_a_complete_type[sizeof(T)] BOOST_ATTRIBUTE_UNUSED;
  }

  template <class Source, class Target>
  inline Target* upcast_impl(Source* x, Target*)
  {
      typedef typename detail::add_cv<Source>::type src_t;
      typedef typename detail::add_cv<Target>::type target_t;
      bool const same = detail::is_same<src_t,target_t>::value;
      
      return detail::upcaster<same>::execute(x, (Target*)0);
  }
}

template <class Target, class Source>
inline Target* upcast(Source* x, Target* = 0)
{
    detail::assert_castable<Source>();
    detail::assert_castable<Target>();
    return detail::upcast_impl(x, (Target*)0);
    
}

template <class Target, class Source>
inline Target* downcast(Source* x, Target* = 0)
{
    detail::assert_castable<Source>();
    detail::assert_castable<Target>();
    return detail::downcast<Target>(x, detail::convertible<Source*>::check((Target*)0));
}

}} // namespace boost::python

#endif // CAST_DWA200269_HPP

/* cast.hpp
2aPsRfZquGgKUAXl5fivfAJ/zpsi5d4XDZzmzjB4Z2JoY105WK/QQ7zH3mdPmbM/9u6yxg7nNy3NSvNSgX+/ChL0ZTwts1ZZN5HqW7Ch7CqLDU0raVewB9u5eWHemHfl18Q656Cj3RJuTXeBexS8PF2t0pv0GaSd+F4yr7jX2GuL54z03w7vtDfQrDFpkXh+96NI7JCbspH6pCk5h5xTmtanzaA4r8Ek2S3LCqySVjmrslXDqmc1QaZub3W1ekF5h+K5F1rLsQIbrW3ohIPQjFvWC+st2CI2S84oU6wCq8UaoyL6sep2AzjMP/Yx+x5yUlHwRUX4xkanEejhLbSYyErohSFyrJwuE6hyUI5HyP1jzBQzG/nM9af5U4NbYQ6PHWpEBmjE3+QLYawJa8N+YyvZBjDMPnaYnWTn2BX2iL1g71kMO4ldyu5tj7DHg5rP2LWxHu1CHh3FJ4PrV/H1PC+o/lfRX8xBUn4CNsjsGKem09Ld6R53X7nFZTM5WG6U++V9WVpt0wW9kl4iv5E/yG+JlProx13qSrFDT8xBypKk9Kb1zfoJXNWLDWcx7ef2Op4AJHlExHFSOJmcIo5G5qnnDHD+cBYjO1wCSU1257qb3J7ou9pqJlwoo36mN3o7veteQsONgjZdMqX80f6f/nH/pR8rKI2sfgAMLPPTOlIxjWKHOT0puUG+kiF0Cz0a7sq/oPGtqdZx6x7WIh7LwHKyZfYmkO5nOxFnqJduvDee+xg/jdRYTPQSf4h5YqPQUIDX8MM8iqrmaqq6pu6r2HqwXgK1/KJdr7/3wksWnrYNNiNBG9fNPRPf9/1//HsRXukYO2pb5F19Mp+sBX/VZttYHvsnuwfobxZ+m/AumO2rPLlIL6goIcqLNiIKM5LR6e7sAu9lcNtDkeLJZEgvj2R+xVVZ1QXkcE8VBTF0AvENQH6aqv/Wy6DfO5FOz4Gfbug7+iFm663+pI1XCWpyFnk1lplmFpir5oFJ4Wf26/nd/Fn+VYzyhf/JjxEkCtIE2YICAYfGzwsORpynf+zwDlk04pPKZB+5SHLRwlTRYTQlK8c6gCyWslMst13YLm9Xg4JF0uxkaP1KezPc+Ludj5flNXkzPgkJ4iu3oPPL5CF5Dgnsi4ytUqqSqqMaqyar0+oiFP4Dsk02nUcX0d90Tq++F3kr9nfw+xvvixfTZDS5TWFjY9XrQonaY66Xmo8mkS/9wK+Ljp0Aus8HHtoc7AsuBDcxeqS1cbHDPB6P5MTsLyE/01M0rjXGWmFFzvovow9S2cWhSifsc/YDux7vwFfyfOJnsUz8Iw6LNyC3BE5apyB89IHz2UkDzRyIfNZfvpAVVQvVWy1Rm9QV1VCP1CvBQzfh5UnB3sW8yl698N2ied5Kb4933Iu8j/XB+8+LbRKbFCY9niRyTuGaXliNFH4W1MpVsFwLOOsOMM4PrYtGIjv31ZDHN5GDVv2wm+PY2eyndjSegRfhgnvw00ZIutP4On6KP+UJkc4mgKqSOL2dy04217gr3Gfo015yJvQ9qya6Kthti27oTfXSoUbfmpL+wGBByDuxw8wVl2SHyk2ie2hJaw/7aHfmRpQB29QTTVGVnd0DblZVHGv1Wn1RP+nN+pi+ogt43DNeC2+Vl8/8bsbDH56YmP4m/y76MU2wKdgVuQG+K3Z4rpyaFEJiXkSeg1T7UALdLMZ2sXfQ7SLwwE7Q7VH2HHuhvQ554Yh92r6FVXlvf0N3Jue1eWs+HlUUG32SRTDholPqicaik+gGVx8lZiK/bBY7xD3xXmRyhjqjnFXoHub2ladkW1XG9DWjzJ9mtdlgDpt/TTw/ud/Ab++f8R9EevRU7DATVkeGP2wFUMimqOB/QVMpoArRxGBxTZRwkru13QYgqenuenePW0c2kn3kQDkHRLlJnpQZVS7VXnVVw9UtdVBf1dzrBaU64uU3m5Ga8vvF/Gr+JP+dHxUkDlIH+YI2QQ/02OkffHcrdpjRLNKbLCb/kB7w8PzWOGuWtZ39gnl4ArLNCGc4BV1KJ7KJunjuFmKve9n9XQ1WE1QGnQOdPtq7AirKDHee7ScJ6oZcEjvMSgnJT6QpDeBSH629rCmfAc/N7LTEDJ13zstDqqxurFuFnP1Ue94M+GBKc88vEZQNhgaRr6FHvpzzGs6eBd0/0TrCUoh4Tgl49nPndzcDZqCzSq1rmH7ms9nkXw+5IE74uzZZDi5ZQedYpW2fb+QVnCzuJfeW+wVJajh8rLJ24PKxTCKTyuQzRU1t0xGu9gVMF/H8OCFbJAPVXrVf2k14Dz6fL+c7+RX+L3/In3EhfhEDxFQwd1Inu9PQ7QuaKSx7q7h4lt+giiughbu9xCaHKWSMKW7KowbWmix+Id/yy0MnDgbHwnz84/ki73u3ROb/jfVma9lX1s0eCU9+iMxfk7fk/4nmzmSk7gvuXBlNRRWNE+WFd1PH0/Lw0Nl2Drj2SL6YH+G5xFZRxNkB/5ZQ6rheei+rlw8Zro5pGgwPPTFOVOTbcG/odWslqyg769eeBeafYir6V1CNzYPp8K844ZnBd5Ic2eME/UBjWhuQ2z9Brzrav9kT7eX2fnsQH84LiepitFgo8jgXnBdOXDebq9yqmIeT8ryMo4ooGymnBiryvrrlceTIZkitZaCWU/1F/iH/Qphbf6zVQlbRbmRfQq3F5iX4J3HIGYd1ygztWAKXfymzqJ9URfWXkro86LCLee63D/oEc3/wb/844b3ETXDbfNRDLu9Fp9H19AhoNL/VACRMmYZjVMYct2ar2Btm2bXtX+2/7G78HU8Ghf3TeQ+/34V0/N39WS6X12QBNdtb7q1DCslhPL8rtDxO+K5TbFKTdCNjyU4wWUIa+bpENtqNDqajwzeyb9H34M7coLOKVuRW6BhrgZUAK7oUc1cLKfSw/RrPx/hP4TvjI/gU/hdfw+8iM73kX9DpiUVmUVnUQIe1EdMwr8vEFhDKBzCK7UR20wc4K52EbjlwyVU3JwhojrwuH8pnsjCcYKc6pe6ohyoPau8gyCCN1woasNn76Dmmm1kPvWV+Z3+Nv9tPHTQOjgR3fryTNzdOyPEZya/kG/mDZkJyT8ROgNsteNMUdH4eXgmEcIDHAh3MgzMlc/IhYY53Tjmu2x256SrSSiAryvnyH6x5StVEdVYH1FmVTVPklMn6kc4Lfd4OopZmjJkF39xkqL8StZYs6BXsDvU/TpjlkpFW0J9XxKJt6FLM5UtaAnz7Jxg7BkvBWrAebD17zgphFt+gLzrzrdDj+uEJcSwnufObMxOKktwNUIGL3I3IcRmQm/rJGCqfMmo8aucdEn1tdOdFndb72ZsFb4xlSphr5pGJ7qeGj/fxt/pvfT8oE/QP5kfuFeyKE+6VpSV1yQxyk+SkXehcegfJt7HVybphZUI9TQbVprDL2APtLfZHnk00EIvEQ6TfaA5xzsEBqrjjMUNL5B05DLMSS5fQY3RVKNy/Xi0zwOwzyf0q8IGmqORtyLRxQob+gxwjCWgHepY61nUwexkQ60G4VEkQ8xZo0Rg+g6/gu3gMQbAmkR37h8KD624JM0wTN+KUF9xyyDKj5WZ5XGYDOa5RN+CbpXQNcNpjnc9r4nX2DoAMpGkODjgEks3tC38wPOK2/9ovGlQIJgdLIm+43vqxNlHkZ1ILZL+BxKQpaRPamR5DpedH0hxuXbDuWx4rH546fWRxw+8IrLMP2cl5dt6JD+NT+T302U+iElbqpSBOWxD2XSerW8+d5h51U8uicpDcA11Lptqp5eqJyo81Wqwf6NxeU++SlwbqNM+k93v4C/2Hfp5gMNL/2yDqZZzQ03uSYWQ6WUa2k5PkXxKfaoxsCW2GxGsj4fzG9rKzLLDb2qvsT7bL54CwMolCcNR54qi4KQohU4xC3Xx1crkStTzV/ehmk1xOkDvlWZldWWoAKueWeq/K6G7grEugWuGV8iZ5CzwCv2hntpqjpqBf3W/lb/SzBXnhqgODZeEbBHGjHob7kzXIZKhSWzoZapTSymt1Qz0/t4qyZsjj6dBjA+0YPED2mcmriy6iJ8Y2XdwRr8QXuFwGx0PX93ImOtOdec4G1FMut587xf0b9X3cveY+dWPIeDKzzIWc1kJ2lJdkCpVOZVflVU3VWHVSPdVl5aLmyoR3zM7qAHXfALPaGqlhKHJ1PNBgDhN5k2MHavG4+WYy+gV8D2ze1h/hbwfTXkY9pA0yB7lA5nVADcODGXi+ncF+sMO/wYMgKmncqBLRoqISkDykNKlEGpNOpBcoaxU5RG6hlz+T6DQBTU4z0Nwg97q0Kf2N9qYD6Bg6lS6mK+k6OMx9+ix8TyDydnk1q2GYYcdYk6x/rC2YpwasE3JjTruiXQuM1g3uMwt5dSD8bg7/m2/je/kJfo0/4C/4B55IpASdFQKdFQefNRAd4NBjxQz0yGoQ9UlxCUqRwMni5HIKOMyRTgWnqlPb6esMdmY5852t4Z2fs/CCWG5q97TLZHFZBem3sWyteqlX6N7yuoquoxvpQXoiEs8DXQHpvZO3NdwpfexNNKfNDfPQvMc85vO5Xya8H906fP9nmr/DP+jf8B/53/2cQSGwzdHgTHAdlfwliMoaNyryRwRK0XK0K51Jt9FYVlZLW42sYdYm64T1EknhF7jjAnuffRwEniDcy2zH+yPZrOQ7kBjP8us88hWODqI7EvNQZ4qzyNnk7HdOOBfDu3dZ3eJuWXcMCGK/ewYeF1MmlMll5NZgU3kAhHoDHlJOVVcNVVP1mxqiJiLnz1e71XloRnZdQM/QC/UGvUufBnF/0rG9vKBu5dXxGiEldfF6Qt2PeefhNDFNfCSMfOHOXTPT2fQ2A0FUC8w6c9Hcx7ys9Lf51/w36OIiqKWRkRMiEjfySndUDJKQFCQSSW88WUe2oXbuh7dbBG1GRyITzKBr6AZo7xuawEpmzbFWWuus7dZF66H1zkrGCkJ92sBnR8Pdt0ErH0ItHehlM9DbAzsmT8YdHnn3YixfCi87xz/x/5BXkglH9AG/rIQW3BW/OA1QA5E3SG45X5xSbiO3i/uHOwO0vdONvDWTCl1WQNqyvKwn28nf5Sg5Sc6Gul6S76BdKZQEoVQC7TRErYxUi9Q6tUUdV3fVWzBLZSjaAD1drwHj/osZTAYmK+bVRu1E7kpvhh84pgrYsJk/zD8LZ0wT5A/qB63DfZW44bnjGfqL1dXqA+X4z4rFUrOMrARrCA1Zyf5hW9khdp7dRm74yqpA68bb0+3yvDLIsR6fyKeJD04hV6MCZiGRHXaJrASPbgl1OKRuqszaxrqe0a+8eBhBP3PF5PQHIA8+hAskCFIhKcigfMiNccOMkAir5JIKULU1JBE8qj89QE/Tx/Qt/YoezggfqMK6spqiLXz5scjhem51tyVyaw85VP4KB2yovyMB9vBGeX96G71uflSjuCFX/USrIddPpQuwzqmgkg2tVlDKnVZL1geeH2Uz+xe7ut3e7oGcPxLEu8beAQ64DJ5KxFPzQnwgHw0aSBTeXG+JHHZCPIHXfBZRTnmnCrJCO6efM9yZg7544Lx0/gvv+dSDVz5148js4Zs2JcEwdWVb2VNK1Qy0sEStDc8eout46PvW+nek12c6ppfEK+QxL5IXzpjCfgVoZIqgaNA1WAsHP4Sevv3jvLhj3PB9vsipZ2kymkwh85GkS9EXNIlVHM+Wjf3EaoBGh7Az4W3TE/aN8AThg50M+ZogbXUEH05Drq4qhiBVvhVJoVnVnRF4hoWo0iPOaeQf6VZy80tfHpV35TfpqNFIY3+qv+Giz5XQP+vOehx6d7c+oZ/rIvCtJuE3GyLutQyqddd74r0LvzuSwdQyDUxSEMDv/jL/BCgoTcBRgeOCf6D04V5a/x/Pk4X8SS4jF3Sgh2lSKHZjaHRqlp81Z4vYM5Yp/N4Ts43dwN6OBOui56rzBshNd/lbrE8aEamGsW4smU46sqzsJFfI3WD7vIoopUqoX1Qt1OZvarZaqnaofeoIOPKJ+qZi69yaw8eq6oa6je4B/V2t9+hzOqmXDp1UFE/WEjr0J55qo7cXqfecN8vsNzH8HH4RX/ul/cp+Lb+73w/ddcc/FFwNz4nihvscb2kcK6lV1nrOCqCqttln7e+2J3qDD06Jy/DgyB79C+hBEjeD284d6k5217lt5SP5QtZVrdR/ajiUcRfyduQmVmQ3N78paw6as+FbVC9B2hmDysEApL0f76DEDZmlGRlJFpC95Gz4Jnde+hOtTQfBAxPB/yJveHaH8523r9tv7dlImwS91EvMESvEdpHCyQ/HauRMDdX9GsbF3Gbo6/nudjelrC8HyCnglliYz0AdhPbE0ol1Jq11c53Hm4j5+QcrLpBD55knpghcfr6/xT/jf/b/jrzBAA7/Mb7EpAnZRU5Bg2PTVNTQg/QizWcZa7TVg/3OnkbeFMaqNgaDruNb+AWeVZTCCIeJok49UPgAsMop54kT000Jz6nujgarZJUVZB+5SZ6R9+V72VYtUCvURaT2ZfqbTu7lAJP8a674T+EMBeAMLHACHQTBT0HpoBpqcGaw7sddgl1xw3OxYaQs1GImEtdTOGV56OIQpIS8oM+j0IpPrLbdxx6NhPrFDngTfpi/5tmFEbVEGtDeEGcyZu6rU95t5U5E3osnq6Hj/4YDPpFvJVEz0D071Gz9XidBZY30LnvRTR4TeQfgrckA9zoJZWwbbAoOg36iTsUNv6UTRYqTqeQe+UCigXI8WgNUc5zeowWsYmCZ8dYry2f1WVs2ne1gMTC2yXYRXpW34P34Ir6R70P2Syo8uPc2qNZFsHwMJ7WT03GdsshZ850lzm5oVi63sFvaLe82RvcsQlK97L52S8GJ+iCtnkQGTBHu/axD30/Va+ExXb2VZrep5P8ZfhHosJ8Ds1oVeWt1ZNy34ob3JKMIIYq0JHNIRnqGRlkZLGGNtDZbs9lFdosVtEsjsc6yk4ucgolmIpOTF5nmJ2egcx8ZNIPb333lTpVz5Rpk/TyqEFLf72qxSgE/qaqb6g7wlPs6OdJFCtBxe+T9nX7McE/oh4+kI3fpcGscFD45yxXm8vHwsix2ZG+6Df/MmwjpxIVGDJKLUDc3ZQJVDevCoMMboGdxvRRece9X76LX24zyN/jH/chfnYv8u89JStqDXqftrd9BT39bt638LCGy/gh0toQf7kW9fuM5RcTVD7lv3VwysbJ0Tk96Zbzh3jevpmmJHBhheR40CveS4oV7c3UxTwNJcbhd5IQriVUJ//pf1lrrVzaSHWcRIj1oZ+A+b8Z/A5V+5KXAnDeQ3JMj7VR1f3XHuSvdpnK6XC+PSKGKqvq6rT6gjyJPRHllvb6gpzxwlCYmnp8TxBhZr1rIXzvAhvFC/69GlpIT5DoZgKqPb6WzMrD2bByLBkdcDNU6ZVdEJSUB+44B6e6Bdn1CeijnNIV6HXNugAHju8It4/YKvzZ2PfyGlS23yYPysX7qZTTalDIJof7F4P2R75vt8e/7WcGo1YLZwYrwtC+KxAtrpghpQ/qRieQC+U5m0v9Q43etNKwCq2jPt5fa+bjho5D3ZoffbLnEq4n64RnO32I5CCsB8oxB/fzhzHbWOYec824y+R3z
*/