
#ifndef DATETIME_SPECIAL_VALUE_FORMATTER_HPP___
#define DATETIME_SPECIAL_VALUE_FORMATTER_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <vector>
#include <string>
#include <iterator>
#include "boost/date_time/special_defs.hpp"

namespace boost { namespace date_time {


  //! Class that provides generic formmatting ostream formatting for special values
  /*! This class provides for the formmating of special values to an output stream.
   *  In particular, it produces strings for the values of negative and positive
   *  infinity as well as not_a_date_time.  
   *
   *  While not a facet, this class is used by the date and time facets for formatting
   *  special value types.
   *
   */
  template <class CharT, class OutItrT = std::ostreambuf_iterator<CharT, std::char_traits<CharT> > >
  class special_values_formatter  
  {
  public:
    typedef std::basic_string<CharT> string_type;
    typedef CharT                    char_type;
    typedef std::vector<string_type> collection_type;
    static const char_type default_special_value_names[3][17];

    //! Construct special values formatter using default strings.
    /*! Default strings are not-a-date-time -infinity +infinity
     */
    special_values_formatter() 
    {
      std::copy(&default_special_value_names[0], 
                &default_special_value_names[3], 
                std::back_inserter(m_special_value_names));      
    }

    //! Construct special values formatter from array of strings
    /*! This constructor will take pair of iterators from an array of strings
     *  that represent the special values and copy them for use in formatting
     *  special values.  
     *@code
     *  const char* const special_value_names[]={"nadt","-inf","+inf" };
     *
     *  special_value_formatter svf(&special_value_names[0], &special_value_names[3]);
     *@endcode
     */
    special_values_formatter(const char_type* const* begin, const char_type* const* end) 
    {
      std::copy(begin, end, std::back_inserter(m_special_value_names));
    }
    special_values_formatter(typename collection_type::iterator beg, typename collection_type::iterator end)
    {
      std::copy(beg, end, std::back_inserter(m_special_value_names));
    }

    OutItrT put_special(OutItrT next, 
                        const boost::date_time::special_values& value) const 
    {
      
      unsigned int index = value;
      if (index < m_special_value_names.size()) {
        std::copy(m_special_value_names[index].begin(), 
                  m_special_value_names[index].end(),
                  next);
      }
      return next;
    }
  protected:
    collection_type m_special_value_names;
  };

  //! Storage for the strings used to indicate special values 
  /* using c_strings to initialize these worked fine in testing, however,
   * a project that compiled its objects separately, then linked in a separate
   * step wound up with redefinition errors for the values in this array.
   * Initializing individual characters eliminated this problem */
  template <class CharT, class OutItrT>  
  const typename special_values_formatter<CharT, OutItrT>::char_type special_values_formatter<CharT, OutItrT>::default_special_value_names[3][17] = { 
    {'n','o','t','-','a','-','d','a','t','e','-','t','i','m','e'},
    {'-','i','n','f','i','n','i','t','y'},
    {'+','i','n','f','i','n','i','t','y'} };

 } } //namespace boost::date_time

#endif

/* special_values_formatter.hpp
oyWQuGXeffwHLx4ltje911uKgsL2G/A8fXqMNcucFcfTr2NSUg6iyQKqw3HPNW+gh6f1TQ5u4qb1xWxrC0dwx1dshN9NiA9609Bptxk0lLYXIThK6PIaQzFcJ4fZ/wYUq4jGlLEM2b6HMY4hiuWd4LpIL7xNZcfueJprLmqHVzXIyiLuJSuKuJpW8YOu20srppYLLJaF422l0fGoUrfnvjvCsbHSfG4J2hZKc1hzrDJxGOnOuNgHCMFrrlTNrLblRLR931z3ILlbCn4E1iEVjSTkO2GNKZwN+VaLiowYua/i0k5ag/sn8xuXMb2b2VetA2mKL7niazbDKmwuIasw8XPq9WXDT0nNfsiSnEKU4fJO/ixdgaIM77U7/+O3fwfMy8ZK1M65W/+GVnDKxySimh/h1MF4J/FYWgoOHZiT08h9vl1dHNRpcV86j/Ii9G2akag79CzMrdyNTrgWOhcbsQPpBTID/JT5Zrg1JgZaMj75dro+hxQQi+keAhgxQfZsbY1Er7v9rcwW49KBfozxx35P805LX58pkq3Rt5MVMzY/mH9wkJjLp0zTimNIH3Fs5wf2uvofTxqv0zK+9aC8ryqFw/z1+bcO8ywfzgX83fy80U5QDNfHZH5Iiwwtu0se9wxHxp4FyjrDXPvZXREpiPqedfYRPU78kI2JUpnAF0tMPrRShlyUkTEf9D29gk4xhUvNZ8TSQRzXcn0/Ds3Zc1BRv6mk+Vxxus6HQrtZD+bswiv/7pV/9koT+XUd80hrRPxgbbtOYyBdxmdyEWg4X8dmJQIrYbiuA86jaV4EGc64naTwHlljLy6V1NhGf3xqMbp3Vklqbx/RM6uheB5dy6+yxvIvfaRTbFzDj+KCKTqhElDSmjeLTjRLIhLba+pch9b8QoKKgqnBvvy3JnVhe4uLMnCrE2MiImCxoSyZq2RyeIWEba3B1Sun7ZnwsHTkAGgHfZaXTur+JK92ljfGpGTv2T7DsOcnjA36XnL3Vhz5y2KGIfVzTZ/4tOtzt52SlrdCL4kg3tniJkT+o5s5lgk1yATRPLWGxVuZQK5N6TwlGwMzMlN1b4CLoGkJN+4MmjrdQBBxO/ta9Vb6OMOzy+LuHnqzMd4EQqD0QplubFSblI/PlAlsPnIJDp5iDcO9pp1JJiiNv/1rfY7J+L0yjRKPEV4eE7hlLrH/Dv8AxY3disjwdDdRIBhDkbMfnrEMpj5rhN+79EdXhFeALc/2i9DugvHXqZsyPs8UYC6tW5jnaFstERhbkRf27UFuUa0prE0zcSkBsteSXeoahl8sKTB2aR0clNa/gRBqR9PEZivhw6BkpaVWZ6m855tM9U+d3EKzuIBtoaYb1bvwJVCT5oKouOl/Qct/Adq6lN51C0U6nNKwQxdY+4acMGoDEuenNASyaS9TLtiZwfVR4eqq8xy21gnGm0EZfAEcZSXJbIlBB5YqnYjGdYzl9slLi8RLGmOH08RPCoxlVKYpw/2FFjFQPzQVHbYPKP5Ef/JGCe2/Pxsm/QqN3UrYt3/OEArZVn/Q+rtu7vYS2ToPQ9uz4npdKSdXMwXM5v/IOGpqvlILeEml9Pg6HHxstB4xktJcya34fmvb9f3WNus7xWNL7yaO5CJGmFeqPC9xsa7TIp191TPlLpsZiXMkf1zBeDpWydchSn81EsagsP5C2eKCZuCDl3B/usyRjeFN6siG76Wp7T0fzguD8iM2jQe3ZcVs5YemIBmjaN77F1A4MxH1nurmEtE5O30p4g/386+aTtMQWb7HtKMI5x01qP+cfpGesl/S2fccCoNaU/ezW9RYPsqqKzV7gulgrR6eYsp8e57grKMxX2ec2lewnHrGhyLsdaprJXdP5F8YxSjKZZI1enqARSM71VRo1oKReU27Yi2blS+aG+3JCZadZyq5qysRrVqJ0uYoTY48oRqRc6gXg1uWi+VLSUDml3b9Up7HD36z4wB9H/wC1Madq8uyR48hC+nSOjYVJ8L1lxnDKZBjOLiYF466nvwdO+nOjZHxLkWU6ZzOy34trIPKMo/oFQuqRCdHAMXM/i9sExCVRtt/hWnsMQbej9w1LI17LC2bMLS+BErrSkAJXARabN/4NjVOTuFjpp8stcMn9SfBgq32sa2l7eNuKtGq5I7f99HzEkrjlG46e7PsZiLX05wiUJI9bj9iv04BfHZe+DayOpPdPEdfVJjGtTpGHc8zTLVLDuOkxHw4D9dPmaqj+iUoCREviU97T8bdK9BGB+34eSGzpEecMs/1ozo1b5g2GlFOSc5XjNAl9hej0KEPEywbxR+B403C7nRTQdRQorjtenLSnL8O7llRsxeMhK+yg/Q111iIePFrloAptjewdMmDmwQ0wbmoifVi2Mtf3tNAQ+MZDuyEtR+Rc7hLk3e9ZqKOeTcf9CxGaa3MV8NwCkLQuzODfBTM1FHsjIDx9T0jXnGkElG9SgiaOACzEQWFs6MTxajqqKsscud2ibfPcHsYGnQ6DHV6mfYfsA+Kefybs770rN3o6Cm+u1T3ZcJn7atBxPsjb5WDNdCaPIuU107kXdEd1kawsTbakustSfYJqnKr+7qvKRjFBfjv70/+QK34ClOFFGP2MW2B78/8PSiOH+TIO4Z/h8tweKnQgxUFsdDm71P+FZ0AtSXd+6TUHp5v/f62YLlLnK/PeGnJVS8c4+SPADBb33NYMMfoastJUFc3SvxQHW3OMvptGlSJ+d5sHe45ylXFWTp9b+2+7ua9/U9A8PPzHPOP6I8062RVKsEmatW1hFiwkNQozsA66k42mf/wNyRz9WftAITAWScTUFwFu/7EWvBLlNaWHmOOoX5MnzLTy3NJP1rHtpgPIkiW+7npUIKjRc497A0FgeLJXeb5r5rOb9hvl9nmNPRunirKHRxVVBBWTxCuoqZHPojVCeIek9n9VZK8PUJalB/k0ejxI5YSRlAAFSzq07yW8SFORHHgievX/krS2rrq2F6iR7mdbz3YLmMIyuJSpAcNS4MEHAQZ0kNGq8+Qju2+Ev4mGKPwR4gPFA7kQv+d4r1ibZgO+afg0sM+TKkJpxriDuKXDxm0ASRCFTcTx3G8ckl1Hpr9iyRioE+qqzNH+uWNdnlkNvSWf749/GV2Kejxwjh0eWHcemlvJa6mLh9wqaUWCSD/KeW63twhgjLfN2+i1mN/3lSZd2nPsWl7ZpOmEbFvrIRzyFnfWG3lkHOKiphn29EjvB/ia3/s1+tVkzm2asVrnqqViP5HGNfwSpgxD8GkEEMEjp6Puh3BaJgWztxUDxtXOoJTh2eCzm/wsZnMhaa7Km4txo3/+MDxISIHaA0hoHKN4OpB6hTTABW5UCTm8tb5EsZ98nio9qJK/jyUPV559fS4x9EGBVm2n4DoCXFU7R7ScNrVzN+6Wx22/1rrrGF9kJ53SQezGB12/rbuXTdjxni9FfRnL4SBp+NssoJbrdSaDuoqOWejP2IuKjMBhsSXKct0i/dNxHTyL7j+PhuvOGEdQIjpnAhYhX4V6tbFpzhfztd4/MtUFrhkZqz+nuYLNtZEBuO29VSEX41Q3uhhFF2TFBZs9ykgDWF/90HUAW2ZHNJJXNzXn27ufgTZ/UhjDBM4vBDhQwAB2m7/8ltcnLvrFZUvVMPDUrC8skNHS/4eNPj5JeiO64KK2qteEfx6IWNgvaWh0WB06JlDVkVObPPkC46lDl5+Teutl25HkZXR1dK8UDzneFsLBnOelxGuFOw/tM+bogmWJpoo7WL4bqkfBWNfstRoTnGK0e514f2tVJ/Th/di4Zh5Yx4ZeZduOQnITCE5ofDFMy1niJhTYVieLt/I/+jS13VPz2LU5RQOqCg9DYFIJ8K6iKJu390Wd9WynGLu5bRW4JS/m+UUlTmBR6AF5mlKP1BFshJiX/RLQ7j5kBNQhpog5Z+QTdIvLdUWgw6biBp4EIRPCsl0S9IO849kcfdZ/8wE/uLa7+vDjlCBeXqcpSCfMol+iEt4/2l7r+Rjazk1N3J/PuRDallC+CbYfeQo9E7GsOngwHkXZ6Gx3KuQkyM5lrZ7EhWVoXU/+OJYXvHJLaw9NerN17NXa7UJarl3n36X/60f33tyIaCv68fV2k7zCwEv4Uf25rSym6eV3AXQ27QWDOLQn0PtY90/r9MYuXSjvNLpzHmZNXnU002Chwm6OSO/c/3UA9Tp7MctxNyKfV3qeIeKwsGiqnCw07iLAczpuRt22yLuT9RvCboDRRhn2SMejIX1QvkxLfA4wzlG3DX2IevgnYuS4aOBEB0RHXFpUskShZyXyYyp15GOUizXyNLMA6uixRpiDV916+1ETr6uGyLaVwhQ4KkMvzrTFBXsAwPB8H6maFf6a6zchfT6C9KPSQiKKql5C6mlxrsi6L8s/fE87bqT154J839XUfS+upzA3ldoJB92DixUEqfPw6DgVHfDZIw5WvnnY2//S44pajbZ+ytT7V17b8EyfevKHvIxdHR74i5AiTcSy4ML0EzP+GtoDkNfFHVw0wq8erfu23pL1yo+UMCyTz9ncu7OM3wpxtLhyJbySc9JPtpEsv/eX1ba9o7IHkh923cnQmXH4cxlF7JMZVdBTNVR9tbkIsGWIZ0vMIe+ZK0Q2j+tNN93M1ysxenPOCm9lo7I3zo6jnvFaFOJRhwcjM0PyvA5aPpG4cKujrSnIWYmuHR9snaLf4p4qeMBYmxqw8LzQmeu2ZT9rRuy4MGJmc8nk8vN9hoKIuLa5tw1LvGB6PLh/WfRWbiRWv72uuw0CUg7fo6mHTZNO6w5jtEbq36fU6iC4H5PhPdPxRcdUxRa3zFYl2S/pPx0TJRUJRs+JhS4ILr229qFh0MnPjDEiWutPcRb/XJqe0MXghU3pdduSActibslDtefTNme5I1NyWOkfiO7GPnqOPmwBp2GlTtahk9ZMBj0d2Z4l/Wsnd96j/ZLrVUkX4CJ521qwmK9LQMt/e808/63JDiM9zm6PlA22N2zEwmF84XjwQ3wQ6YLirC+099u9yPWmd87DfMtCRYCUxJUjL53g3pB+MLoGm3OwJpOQFqlVaoO8p8A5Ab43lFo06t1qv8HMxGIE/UiAIBDS3VdS5LjOJK9yxyg4wzVOVVm02aVVtYZXTk2OypJSSzxo+EnUqXL1kabuUCuYjHw/3MoehOB90BSIAg4HIDDPZgye2yjTyAZbfN2mG093Krmxo6d1gttntekbH7HM7+FDfCt7S9lSjaXYdFa7I0jcfh7FBTfVYaU/CJMhTQzzHaaZZJrywzOz+TyK9YBdJRSqxtGpTTWx28dhX7yQUIhgnpdgViNkZKJ1wThlQruj0Xs5LcQ9l4Jv4r3dZ8bufaMGuZVPjg7r8T5sa/QRJQsjTcKx9S4Tz10XGXJ3em9q+5mw4J0+wblOHZDK8MTyRcjl2b395TB/+UXaIenZueT0N6KTvP+xicSnCllXlK4VWJWGzRu5/7QS/jbUHeRdJX3dt7Hqjk5Y6PLrYcRmYD2uX4ofcPnwwW6eUVJF/0lJjYFl+nfinjrD9ise2pB2Ci4v2yY5jNqGcubTFaATD+zW8z7Ex36/jNd/WLRgoYyO+f1gup3bXBADHf78pZBq0VBKe/QtcvsThWUNF+Hmf3wde/4XsDmIt6pTZlRd9FgxN81tEOe+mIn6rdv5JTZmoK4CH1xJJLP1XtnHA9N7AEVtKMNueDSfj9JvQjEIRgpY+y45msiDBQBWDpyJViUTYLl63OG94fLUm/2EaWS9NRMKSNt0zFMPy34A4XmRqE9XwCVYfeyV8uKNxrE1mS3H1RNXJfHKmqJt/nKav82t9FuKO17/XGFbT7cZnIP21iPnIuYw1bHOBTD25zS3fT2H+VJrh8I9eMUA0laSS/oXESwpX0J/oZHa27XZqqO+wTl5SpMemPFqezOQX9RztULw7oN/8m5NwNd3hh0Ih5R3rBuR8Y1Q32V91QkPiHRu1tTpKCzZvZL9ZO9eEBr43U63hv5Ja4jheUUP7GhMldGvalBBbMwpaNNbVHJOVYVXqo9kE5JoJUl5LTdAb2GQw5Yaz5njs1f6/Y4/Nus5hBdKrLeZnWF9CVnvcGLbB+8xZMqwtzmd5V02x37qWoInIGulpQip+zY167D/NSgh7nfGlREmHm+Kps8BLMWSdX2bukKGeLJItH5a84LCBWCH/xq1eCcgdvWqly5WymOFUCnwuDFKXD2m2k+VXBHOoaR61za6ctvX372dkDhsEA8Ce5pBkh+S1++/PaUUR2bjxyNmPfza5UTvXeuZx3C2ITGVib89gJfEVhF0cblzjr1L5D91CALV7mOY4660PF4KFqn3yzdU4wosNIA4MVZ27Zt2/aetW2bZ23btm3btm3bd//734cvmYe2adKHmSaTtlMUm1gEqbccAilOY6TzW3cTB3jqxHQ6zEabx351oJk/daFbQJWluB+P5lj8OEHaFbHHKfaWUlp0TgsSvrUnhx+IHnjaxxZZzeDMceVDN3y++G/PtNBG72uHzkd5hrXvQY82bhHyBNDg+uY7R5kxR4ZW7uUKs8UJlKyRWmTIfvlnlEFr52ElyuesKvb0NMF0cvFcsjgFJ56gZw39jT/0Zn93HGruFHfqWHaPNMIH+3rn3a1M2rpDUhzPsLM737FHPtPSWht0HFSLizZIR5JKyU/nmJKGp4nEfHi1riRuCbByVo+8kUT9E9bMoLY0fI/fNvmrlH+ZHzWMp0d9huk9WHWFZCDFuqT3gDNudrmNuUr4xP7LXMdDuJzy0XwnC9nyBy9B90HBTjvIH1nCS1JIm3o4hUEbJwgZfGcdgtwDyjmZSwRn9zJzlIG0YVd82zn6GHyic5SHk3eY4xK21Y0S27EFtPsxS9zCpztjs63hapVFjs6IsxmgfESUkiTwo2zgEY3pF5sNWJyNSsGPIhZfRkSQjp6MS+BW3KpaSlwbGipprtswx/N0zPus6cYTD0KLCRCteOPXKNVpXV/RUo/fVSl9T5FX9SxAiXYa5Qe9Fean/JapP+wP01Gv6WNCTBhSrtfE5avBLaH63lbOZ9n7u+0Lo5bbUCdHoPoJOw4cMvg+pRJqU89T/WFmCYbcRh4Scb2zg+np2Eq1D9BaKTLK2R+OTH8EajgcmD/X1BXQHr8E9XxSjzg2Jm5+qsrcUDdMjQ9ZBMzeA5LrYsc92HISQz0GidQCLxMUwrV8Gvy+DpXLtckoOzVw4BVwHhAZMa7Rxr9Uf6qLJGlzUUK6IhCcosOoO/I86AsmfXX+NXt389vs0SH/7U7ids+E3ZQui0+EQcsO2lCc2AdO/BnKsecsUsU3A/UPvLSkC7mu5zbCU2BKs3ieytEIxT5EoNCrlU0BXibX3BbTB2/3/sef0PIKFTHoe1pr1NRIihiDiipNmjqhAcph6hMbUPWYi0dKIeUB46Odh+uSoasw722M+ao7ofFAtjow/q5GWgZcPNUZ0/e0ujbNaagDH7otiwwjrCLlP5BeAy8FLgCoyC/LxiDi4L/ZH8PjdDrqdhGS5/4W+hSOwmnCJdtJig4MTE+Fan3uUhVYpFHhOG5RpsHPxbrT2607ZzSDelgyHg3z+aJBY97x+al23Y0j9zpbB3YmfffgxLKDaWpUKScEddLW
*/