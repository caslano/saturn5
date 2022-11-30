// Boost.Signals2 library

// Copyright Frank Mori Hess 2007-2008.
// Copyright Timmo Stange 2007.
// Copyright Douglas Gregor 2001-2004. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_TRACKED_OBJECTS_VISITOR_HPP
#define BOOST_SIGNALS2_TRACKED_OBJECTS_VISITOR_HPP

#include <boost/mpl/bool.hpp>
#include <boost/ref.hpp>
#include <boost/signals2/detail/signals_common.hpp>
#include <boost/signals2/slot_base.hpp>
#include <boost/signals2/trackable.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/addressof.hpp>

namespace boost
{
  namespace signals2
  {
    namespace detail
    {
      // Visitor to collect tracked objects from a bound function.
      class tracked_objects_visitor
      {
      public:
        tracked_objects_visitor(slot_base *slot) : slot_(slot)
        {}
        template<typename T>
        void operator()(const T& t) const
        {
            m_visit_reference_wrapper(t, mpl::bool_<is_reference_wrapper<T>::value>());
        }
      private:
        template<typename T>
        void m_visit_reference_wrapper(const reference_wrapper<T> &t, const mpl::bool_<true> &) const
        {
            m_visit_pointer(t.get_pointer(), mpl::bool_<true>());
        }
        template<typename T>
        void m_visit_reference_wrapper(const T &t, const mpl::bool_<false> &) const
        {
            m_visit_pointer(t, mpl::bool_<is_pointer<T>::value>());
        }
        template<typename T>
        void m_visit_pointer(const T &t, const mpl::bool_<true> &) const
        {
            m_visit_not_function_pointer(t, mpl::bool_<!is_function<typename remove_pointer<T>::type>::value>());
        }
        template<typename T>
        void m_visit_pointer(const T &t, const mpl::bool_<false> &) const
        {
            m_visit_pointer(boost::addressof(t), mpl::bool_<true>());
        }
        template<typename T>
        void m_visit_not_function_pointer(const T *t, const mpl::bool_<true> &) const
        {
            m_visit_signal(t, mpl::bool_<is_signal<T>::value>());
        }
        template<typename T>
        void m_visit_not_function_pointer(const T &, const mpl::bool_<false> &) const
        {}
        template<typename T>
        void m_visit_signal(const T *signal, const mpl::bool_<true> &) const
        {
          if(signal)
            slot_->track_signal(*signal);
        }
        template<typename T>
        void m_visit_signal(const T &t, const mpl::bool_<false> &) const
        {
            add_if_trackable(t);
        }
        void add_if_trackable(const trackable *trackable) const
        {
          if(trackable)
            slot_->_tracked_objects.push_back(trackable->get_weak_ptr());
        }
        void add_if_trackable(const void *) const {}

        mutable slot_base * slot_;
      };


    } // end namespace detail
  } // end namespace signals2
} // end namespace boost

#endif // BOOST_SIGNALS2_TRACKED_OBJECTS_VISITOR_HPP


/* tracked_objects_visitor.hpp
piGD3vz0U6I3dmWZilgfGfSGV+agfEwDqJtvQFu4n/RigKrYbZ25YnAy+S3ziP2r37cMuVm55hygGJAMKUJzEayx0r4PEHB2zSXEgBIJN1UhFocUNp5uMWcwDYpddqXUc0fzfAFvdIxQHc8w0R5mPhoeitiRCc9kpdSB+V+qOK6FvN/FqJbYbF8vgVSsH0BK5qvhdMnvPIL0Xq5EoKtImWsU9YfNQJdvUbdmAqywJyq7cJKqzFloagbSqtJHsmBcmq7AQsutmAGSQe3acMHSejhcA0eHFLuUOgTYGVHYjLjyAWlspsRXMFj0fLE5WIB0SJ3vSBExwegy83gjBDKlzOL/VamG/Eg/RV1emQhEdSp6U8q0Nnq1sQWuGHJ950kjFJaTrNo8Zm1QOhCi+10RJsVU+H7+bYaHUup6lRwYwSFWLkEbwrF4XtlbDrexzVCBW9wlGzNCB1B0qtTsWWUlrBc6vgH59VTyHxZrSgvRcJaeEdioTeOSeZP+jdJlwpdjqce/bY5g6HlKlzFZSh/UPK+ocW7xHDP+K8PAY9kMA3kPmDDwre+dQMDzWK+PkWb0OrV04De6yk1Tb3PlL/JthySHWEFdhJIvvV6hZCYLiAXqY6E3OjFj5fxNEHBRR7MdYbIQ3RbvsLe3w3KBzVdvPMuxaF4pIqlNzdll92A15fpsPqhqmPUBzFhtH+ZyDJUVL9M4XnJaMVRGNvXSCIjiqhCtiKIymkrK//r2KUPfjkjf+vZm/ruf/+7mvy0AnT3yjuy0NflLCO6aHMpRG4aLMiSFJaJ5ixEaW39K62CsL2u+yuTNLBwuMmgjonwelVeFYbdon0pf/F00zZu7S96ivoCMpJsN7KjfGx0hil0iNFb091e6ojn1e7UOZMugFnJQPlLc8AmIwHinKU5U0WJtlQcvIbJ1lH17d/uqt+FgvwEzd8l8mrlXULv/ZPRr3KEascgVX0J06paoU3yUvFQ5m6JzufHYNsJgu/lrYm/p+cwC6m8z8RaXqHRMKDYUbWiqDTEUAd9mFihOYav8r0s/M+RIp6L4lb60A2eGAxRbUojnOWBu7FiyWOyi+kvFfFe8lno1UtdkdKySLdHaZQS88T15MApmKwmI5xsyTo5ix+qPattUdcnJ8uMJQFQyOYlr7YJ3eY4YSVRQk6q+S/5jfbupsj8hTKMp0IcOWeYH3OlXuZXhPI+XYWFvybDzoZn6W+IpgNq8uR1/vp4m4p4JKZbHUkJIzm0Om73isaYCUozt7rPZD+/vNSMzj2u4qI3WuizLoZhg2fYWQTTJyS5P3VKTmdwt9z9IzORTnIQysDvEh93+cV8YQmtOXiX20Lrfx4FGaoC35NcfYEViU3SgidtWMWxo7/LJWqZ0oU7WnuI0koTr22cSGqeyaqV3y1pqVd6YpVb6O7fSQOOvqRQ2Q8QyTBOBMQ3QSePcZdlbV4GWHZdjhyIiiZYtx9+KkRdg5Pkkimf4xLrk5n/yLOTbLGeQIzaHreYw0PTTv78wpsg5xBRZaUeQNmdDELP2oi2lOsKuF8uxyc0ELNSxAcptjr0FiYtEGiNGE2yJ9sIDpyzl0nW7ew15MyqWWz45aRTtJSHJ88yOxGQjrQTO8FFldYdizWEW9U1YtJFYEZDIdELMCk/noNBbcE6gGbjplm4jLH3fhIsCjPHljm8qocJ/NjoSaLsfmJGDVUbIzUFwrBOOosbk/V/qL6kOgtrhTeY/BAPRbhHo8T2HldHcjmC7I3AMEUSUL2WwUwyviOSEyisqwPc/jbBEYTUNcsl1JDw0pYwxph7IsMO5wMtTTW7R0TCJrd70xOrP4bFYzrtmmGgRzfR+tHjMJe4eK2z+oCuaT9Py94z91v5nZfMhL76ZKCrjaC1Hfw7/zjQ79s9CSDWWU7ca2WSVFlXpQcGWsnGKSkeaOT2piClm8URlpwnWKWVWMedTVXFneCCwPhcHRI+89HOi02/7nuV0ldny0fHdhn+nlj1z5szkIP/nWp5/Z21uxD6TembWTn2BK1g6qEseob5EoId4KgLMWA9RJMuJsyftxAnlP22IHrkTxrWtPiZIZiIFeLR3IT1r03I8BSg3BaRKpNCJzScve+sLg7gnTx2CGfuYvHnqdXSnJG1MT6B0q7kfljeb9fTdEvBzmk5AmuFqqfMHYiWoJGG9gaY/jM0I5fmfw8PolciwCSqRB7DkZ1/i2Z3ShvPZFgqFqbrRZlVULP5LPPyyT+O/xKht4F2+FBT/Y6QctlX4t5FyvrXP0twyon8CY6UpGaKOLDEl8V/hGWSE2X89mYZAa3XLy+Mx9ibRait4keGn2wNF3H9Y4o9ICjZeYe4j4Erjo5hL7RxCAtf4nsMKRS/T+V8xtc8qDuE4G/sPGEYyRxWYN4dw1oCPTxppT4o++KmCnapoe4gzCCXyaAGyiV+AQdikWLzJ+/YS0UT9CIDa3Q7MIv+630Be4MHKzNd/VvsQdtF2QiSIc3gL4RIV4AybmqYW27r/W2p25R03ZioByj9PKwFOv3i+EkAd2h09xfQyF8iQI3UAXdOsGkpN7rY1TPkYPKD3L4oHXADc/9vPsxTuJwo5w9mUM55eyvXzTil2cEYBRJpn6JbNeYv12ilNpWXYBHrtdGL9pp7NItZv8nRUtx7VzUV1Z/RYV1M/1BRfUmYRkqhPPDo6eTkzBNMVmS0op7Y+rzYZ8H7xdbN4e53S3hd3T8xgFxJ3FzCtuXmeojWJu53yGrqWzdTaLpk3DtyeraH9berAB2cwHg4D7tVLpxc1Fhk+6vqMYs/qRrZP+scNhIwORofKT+8lglJFxLF0orRNoeW7umYt8MLcjSbNdMEI6mB0YDgcrpKvB5RPKJWGQrp0CgSlMmrfOsOoYhcb2DhPlI8Ws18nTaj8xtWfKS9nBfpApL0kC7rMWTFW4TgHGAUf86qNBTjGH/PaaPyTXcQbKKaAzacxK9ny5jssLDw9tbth3Tjonjcg4g27FzSSJ/cX9yrBniNOHJSd284a8RgxEINfWEQoy8jGXz2QLwL5fr5enFP8P/i3SiwYnbxCrRUzb3LbZTjzzz//S1qsI6JfFc4Igi5jwfRynBMcxBEbgfVccRCWNkAAihCPkg+RwBPJlk9sP2uEE9MK9Oex5HLSVUxB+RTAHI3ylo7YKggG5bev5MBs3hBuRtBN/H8YVMTCidTDiyJZsBOddDtPpDN+n1sl/bCO/O6cyBiThLpQ2gOOY9KLytFV4hFXYVfYfyKW7dip03xPdopH3KJyTGGX9cxNeEDEiAeszju9i73qbhQ5ul3vJ0pd9IU+1SVK3YWlTpjllLsLy52HevwttVlExAO5TUwxkuNEqVOf7NSnOqko1ahPdbMxD3/iKhzS5wvgzmV/5SO+XXOUn9H3lZ/RncrP6BrlZ7QIzVL/zDqp54XZ0wkCdLqlhiY7k7eoHlIhu/XKRd22J7+q+sOjc5hv6Av+jt5MdSdHYog8I+b7HAJG+jaHhqucDBXGfGyiLXoL4fOs6ABg9ajzpsZk1mbaCrmeVxpp6gntEuoNsSLG80xjYorN8Pw+QJzPzPGpQyYqVgXKNlytU15Cc6VOmoxQWYY3JJSFSs19HJur/AqCm1aSXiYpFXEi2Mvy9oHUtrqB8zFCmvjrROxJN31WIdfOOWVUoIJ9l39mJAeqx/JVqk0J+xkRXR5xWdIsKuatUFrYa6Sl2Z8XpmTTO7E9c6o7Nj2k8jZmGjXRNF0PqyTufVM/hl7CFCsmKms0umb8IR+lB/GrbZmmLZV8NFj0th5y6l5f+cRof4A0PGO83AY3m93x1iTTlx6dhlR9Fff7GoVrWdmxcpapkh05yjwKVGL2u0rMPnitKZjT98mr+etrM74O4WviuAmRHM23jhIH0+f/i4PNXXIVHJWakt3pmRvDdRSqOlhr5Z5lYvtBFr57mm0dTmmH1XROU30g4ntELHCF39x/71BvsoDruYLrCcvmsFlHf0JqzfKXNBb6vg0o60o5EJ1A6c/M0j/vW3qRWXqe6ZNCvbySy1+dMdIHw2ljIyhdIFDQR+8hIo188Ro+tCVmBhOvOWjOO07z3Psme4nKZD6/9DabCbjgeWwEvcRnvY4xvcmz/1Vqn9ou4h5MMKNcyiq1SnqwV35/JHW3CQrDXigMcy/7DL1vEcEeNkeg70cnb5TDr+kz6Aq5IVWFS96QqoJV/4cKVBXMXJrgVU77CotOLb6OCeDOUXW36FpPnwCcQbNe+f5XuNLBxLkQdxbf4ZRLL+V6/4yInNSp8XLZGOLBze9PmN8Psr7/+XnfF8hi83tW4CvcssNZ3XE5dfffrtP2yvQ6LT5/nexjzHWKPzYFhht3ThF2Yx3EDLVCtGV+PZFjTGTUPiaj9vsyal/BtUcHq9qpUvnfV3MCzFQEhvuPZ9kiIVmw7kKJexUxZjL/RFZKS3Zc7j+V5ueuXnceP3dBdF0m/Th02EsMzDXUsPwfH/rjqRPUr7CxcPqbUATSxvzZqLMk+BzDq+/ZcbhFzOk+GRn1mQHS+Q2EWwvKRGlBqELeD7+KoORYNPCjL5toLJyIk4IQI6MQkvI23wrmVCKlzQdfVeFkpouDFfLbl5w1+AZVgc+ne1HrSs7EaZmnbhY7BxIXrDb9iHu62RtudqZJ5mwWyheY4kbqRp0+XPwuyQ3Ncu2j3Yic+mtROpqE4maM6gu4S9zpEjb9pVlqxf9ORI6W5ns4qMaxTN3751Tr1kG1lM9WAHO1itIps0kmoAn5BTQWMwgghN9YtQraYBLGfopzZTDPwWPMNsbcYdrONFNFJT2GKbDxYYYvJrWfAHtvmqCw+PIw26LMgQ4AAQembFcqAOsgtexfYErVgWbZPado2t1IFxNo4RODo2dpSNUuHCUTgTOPoUC/iF/1WgeLPvqMOKiHw0y3ZuV/Bufpv5hePK/MpAnWDkN70pWcIPb4T0eDGUj3pzPVriNmdqQ6jMAxtC/WpTkq4OfVZaya7qDmTmu7rebeqkBzxfJB6jli1m4dDR67oKEVeuPHPqXhHBHTJkYcoKy7b6ZZIBG9C0t/BTTuB6XjVl6bq3xT3dplYmpxxAglHp2S0vDv2yBLPwP4dYFxOUMfvH0Lb7CgmJqnB9z+konRO7CgiCXiiy9y27QxoqyYNu1lEQM5UhPzp6Rq6kVQMGLnYlzZDlFs1qA1imnTlQn/o+XdEGeCh0WXbJp5ig+gEEmTODtaYmXgF5IPzrYjVvph+duRnxkRWxUuP/3KZ6yhP0hfardjoP6YS7uJBi9/dwsinCnUDU30QmeEPp/mlH/8CmvtxhCy+DiMB0/MNAUXqnA+XYsmOehTNbFzriAphL/qR1OePGIigD5WzblKFC0yeNLDicpO2Iuz81qm7ZWwzyQOl0pgjQ/Ttde/YIqn/ixYDT5gAKDTlIgu7DZ5exSOGtPlNcO6jSuRrHzZOeY1l9C/YDbn0L/MbdK/S1O6kUCXI+BFdIVDhS0Ebf7K1li0MNhK+C75EOtKA90OBB/qTvYXAa+dpOdANwKwdvqDh2N3FcLIvTN5B0cc4ti3la3QsO3w74xd53iLiCNxLVS2ib6KuhwkwgU7kzmqQlF5mMtlOw7phJmJCFqZfTsVIBihCRn6scY/Yg96bRySEEZqbXqsnaOtWD6IBL9ZVTKniI9Y/oQKOQ0giWATkg3mOtyTuQ4kFuSyZFJ0CpoP6t2N+rj4AEK4zSb+0mMNenC3XtnH5bGvAxma9m1BuHNP3UVYEIfYp2v7U0lmTWML5ZP61gjCq3dPrEpUtiEQq1rguycmKrfpGv3XyE+8ItB4ujUkAts47UOblVVH27RsT48NeSr2s/Z+f8hMOMynws1yyfe7jReiJMcp7/391nd8mAhYeZHhIVcE2lgV1Fys2znTRHfyzhcZRIaIQDt7OapXrcnrX2SQoef7Mz45ltz3IkAoilACGeVlYaBHBHeX4bqB6I+wd7BBzt20MBXyuzfybjvnqfshHvarYpezgzQDiaA5fF3bqmsNZoyQXNEvEdzKl3lqDAjfTvhjFM0Pt9qemOKyU+Nm2w3UfHIETZvqqiPQxp0tDGwtRJQO7hef+OSL4Ga6tiDrwQYFWSaIZLgYskpbOfOF9UDrlwaAfxcr1Aca3yVGF+w2Ye1rgUduwUBTijjlA9oZotUZR/USkv5fcLpj5WWXgumjjz77v/oIVkl8MDWWYZUAjf4bdgwLbg0s8arpRnhvQzOUOZ9LwvMxFwD/eNFRTHZsnR5o8M2dyAr6t+3QHjeG9OoWvfqwXt2aGSKUNWUZQXfVGQmt0CZaIb16k1692VjF9rrBBuCr9TP16vV69UYCZ44ca8Wd5NcVfKhCoD9jOl42BRBszSZjMOjBo/aQfMS6bgzJB9S1vNuLQ5ONjNwMbb0eWGNomxOBbYa2iQ0eQypGa3uIY9F+gkxr/SoidqJ/gKJV49A7AkybXr22IhFca+bmNj16CO4OkHDKqQYNrR034+Cusi2hNaakV6FtFQfknE8NDtzoqdsD7mVGsX+fdq1SNh1/hng/PbCNLd2jgypwvNAsZxQpZRNoRjJbTrmr26hAchkcGVdiWxBCrHXr1dtetDXStupnToivek3UdSU2rY5BbsMg18l/XMeySTXdgp0xtAZ5/DrTtnAWWxRsE4GttP2qZCNtXvnE31mpRUBwCkDw2d8ICIg70UBag17khdzqW6Qg4Ks45a7MAAss9NNd9hcOt1K5cdnnjDFG079AD/n0L9CBi/6FwuLPVeWJMqe8ZDoRugHq+u1pRA0dieCacsKClkd25u7gvZN2MVRJ60zIIYZpHdxmVAo79cyMWsuJu1ORno33RKWk/Y/kSof8LURCiEGXIgYHcdFEVCWwPkbkan1iop3aOx3IZS3P9QJeWe1sgtqKpJEwPiVUeLjwDMcP8ffUZoke09EtOQ55dmKykDqOlN67qSizu/vp48JAS98voOKBfLAZhqyBbZxGHGswXb74EOJEtFu3P+fbRutWPIQzW778/iBYVSngXnYG8+6pu4l6QtcFuM5R15j/W+lfzP8sEWwTOwqbiKgSSR7Eah30dT9i+CB5z24iMohSTMg1sDl5DZjpvzPRb3H00Ey8gC8cTViVQDNWheanehswcKCVqi4MEm1oEUMjtkhuOcHZ4SIDRHVfWB2Xqcjr8AfILSeZojDYXo7NQzDaHjbV4NVbsYM2Zewg8Hf5SWwfMJc6RJVpxAZ66uF+qbbQ757mLbQRPB1h+2+FAdDNBOYVMmccLcwsWhh0/1iq+53wtSOICuzvQNoqDPNitnvFKhc20dwolVewnT3yGnUiGTwrTQHE2LJ1eGCHojxhuwgTry+FV2IEwcrkK9exmATsIOdfC6sl3ojy/muhM3cjn9Q02mlVk6jno45lpaw4451TMulInqjMr1BhlauQNGubPk5MhoDerFc2wjtyNmSVDCFnt3ypVKlnmL5kRlywUCnEi0RwfyazkcmaKDK6aqxD6ckC+4nt5WDOnvo2m/msM/0M4UVZswtvEyhXVyGXXbwnS4URUGZhsKjl2EFdRGuppD0goRe3okTPyjA4u6r5pGFyPYcHnzX8e4jxUB7be6ID4KKa7Zvv1CYQ6lPsisXmcL/arH5F
*/