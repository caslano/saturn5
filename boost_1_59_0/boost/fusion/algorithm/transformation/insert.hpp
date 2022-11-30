/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_07222005_0730)
#define FUSION_INSERT_07222005_0730

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Position, typename T>
        struct insert
        {
            typedef typename detail::as_fusion_element<T>::type element_type;
            typedef typename convert_iterator<Position>::type pos_type;
            typedef typename result_of::begin<Sequence>::type first_type;
            typedef typename result_of::end<Sequence>::type last_type;

            typedef iterator_range<first_type, pos_type> left_type;
            typedef iterator_range<pos_type, last_type> right_type;
            typedef fusion::single_view<element_type> single_view;
            typedef joint_view<left_type, single_view const> left_insert_type;
            typedef joint_view<left_insert_type, right_type> type;
        };
    }

    template <typename Sequence, typename Position, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::insert<Sequence const, Position, T>
        >::type
    insert(Sequence const& seq, Position const& pos, T const& x)
    {
        typedef result_of::insert<
            Sequence const, Position, T>
        result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::single_view single_view;
        typedef typename result_of::left_insert_type left_insert_type;
        typedef typename result_of::type result;

        left_type left(fusion::begin(seq), convert_iterator<Position>::call(pos));
        right_type right(convert_iterator<Position>::call(pos), fusion::end(seq));
        single_view insert(x);
        left_insert_type left_insert(left, insert);
        return result(left_insert, right);
    }
}}

#endif


/* insert.hpp
j9tT30eF6tMLw/5hsBdijmcP9F2SDHpJqYuAX5WlxYHqhYFuWE6E2FvhRcEZ3MU+3IjaPByZqmZPaomlbxmWlcTcWQntKpk5Ukm1GI7Iw5jF1oRPieWI/CdVvape8IemzzHLDrlakjV5e86RaLjOkp3Oh5fETuAK3cSyaHsHhRr6saYQZdpZnvA00jfgwlfM0SAJeoK25MMyyaO2avcoUlKTVO+a4XztQlTzx1oT8NykCH1OLhtc949Uuq5OcpPui66Li4YS/FTZyUd7sHRlrSTXFJsad6LnOnkC3dJV1YnXtHT6JcuhHbY884+uQ1huLR73EyWrqWsgr1YbjQX48hcLstfiXKZWU+n6WmacDLsSrlxjYaZXkuul2TJN0PZHO6vuWm1v5Un9f7rRSvQ4JN+CC3lz93mJHNE7utJcFafkStSbJj9NeSnfjWDyWDS4rxzap5Did9+xOVUW/evfyJ7q8kY+sRGPufWuue842ApeTD842IqbgR9GKlsTbpI369BaBexaeV0pjjYh0pZezVoFHWxYrLkbycYlnd0tiK8T3FZOz5cOsY/u7lUtgnn5HogONF26UY/oxPuVQyDTm81FifNW1yxNP+rcjJyCRTk9JHTCRpm6GdkF45m5Fmu13e4dGYw6N0/YSGKWNdm6adGs6TvpUzCTpYc47HPrs3drTxrjYoM955XNxKy38nlBFj2CVkAayHORDhTVFi7V40asRpepBhre1RKs/5Yc7HhyMwLEHSsKWmIPXcrwKy0qtWLaGm4AasA+FrgVelrhpIdYbeBPDu5nYXge2ltX62i1LiITU8ff1oMcW5P5RTxyknurmRthgn5v7OnWCyVr4+QwLShq9AzMgysv7p2lbu2z98r0rNZEDg/+e+VIgvUeNg/eXTYT04D9+lGxQiidy7s4LV0yrN0JNrdWTzIU/tahxDWOCabWB40KljoTqwrAG/JsA7+3XAt3p7UWbFLORJN6RB7va8MZb7Mmas864pbgE3pgTOQ32zqlHPHxHWybbbSGjgpwlk0kRLtg5UasXbkS7FJ9JDqwnuYT4R6nzWRH1MmEhyHe83Bin9znp8xKBeYW5E+fnAd20qfKlhkPYL0bBeSsg2XL/yIZKnCh896iBxfrZ1vSFrNwhJTu2+IHv9CHMURu+3jsAkdMEwL3VAeRltSNOgvJGuOiTDlEEzr0L6qD2BzGGIUZIEst8+H3pDT8D5KorSTcnm2fb4A4eLOJf6Q7BaXg0XBb6snNIErqSVuvUM8oN35B5EFpwCb4ExIeAY/0Kzkek0MMwRTBFEkTwiZYGqIVaxx+X1EITbQdgjZYbDHpBJYSk4wujsRDGmaZJ8NSDoISZxEyCsIMmY5si4jlW1K4LcQefx9RSILUB+scMg5hgOBBRl2EI8uecR9twCdYHMKAwYJJUhgD0nMM80vaOOLe9FB4hHmkrIxSUavoReQ66oOJitPT+gl1Xk2MXbQ2/MfnabfIL7xn/in63K5EXpY/i8kw0nDCsIpx0TB11BtZGcHL6qq7Pm64B+XT8sqrftSI0FZpq6Lt2wF/6BvrNEoP/7f0Df6wN6ZWro68DXmFBIZNz8CWpTXLjumWxQqZnDSVdIV0RuqJdCehjfK+f6gUOU/em/N+NiIMqVdaRqZC0lJ6I/Wp9L/Xj5wzt5Lddt/Mo/5x4aRRMnSSNLLPxFtZX2qNrMT4xNzEJEerSDAMmOJbnXQYZsRZpBGznyg/wSB7NEMQv5qw3/M728owjPBQd4YAzAMCxOJ/yWD5yWCSDBAfBb3GGLEbNEuxQtfqS3KB/fac/wkDGgswllAEyGRLaiiArjPAigmxllT1dx47YwDD2lP62FxrHNJ9YC6VIuwScY6+sf5WmS9pDMEq7hLfhB/4XV6VU/yEzdgx3ydjy/CYWLD8il2gIcufR+xnZkGu6v93v7t20ovZTfCCH3476hvQxuurRnBb435jBr/fOMKI5a92SL8MUjouv+drqWzZDGD2YSf8lcBA5AJuaHihHM5Z7oWgJ0MKX35r+e1RBGb/PR+Q5AJADv6AlYur7v/wCuwRET/CqhLkXsM1gBnUZgZucJmPJcPpF78w8h7kvtMaeteVB7PvIQ/Tjs6qh/zR3e3vKMh1W6+Iqe3kASavl9n/vRp/chxNwtu3UACMYIc9wYodVlL09aCQ+5Cz3zVzi4iHN1NdGrY7/hsrgVarYo32mpQ6LD0+0wH/7Df2gXygrMHjE/Uuy/sLeyX/7OthwLa6mzt96XQ+Zg7cRyI0KVHza/+Ek9yLM32sJ05Nmjlq7wFRQGHyhKEbRj3axvB9pYgX1Etmd5ruMCnR28Rv+FIchFhLuiXxhlfwzrTwt1L0zmLwxBkFEuLe9x5ADcZGPHQgM7cnjwLg8yo80/vhDZDIxtfMhvdsEF9UA5d54n70kIlb0RaBHQoEPPbWFj0oAEjoF5iq7m83FPEhjBLyQSwEM5NjOSDItoMJ3dNe3MM5SIeD/HpnmuEAG0Rg5dj8KMgWTYelLMMMGNsjyg7BytYpp5AfcWThgAcvzI7SZeXA5zwpsAN7D8eiGF0fzwdSDPp0JjMk/TDlkOZkK1SDvVnEMctXA1tFmBlqr+zP8UKZaLT/sdzjGli3ZzzAyf7Fsj/MHcvPsSeMBv+ZVouNentF3RMTgb0JTHr/lKjCDTJDZL3DWYnqtxWBvQoQSs4j90akKfMATOiXbks116cnClLLj+b/JPNG3ezfYxWB7YJTTf6NLgtgt982uCPbF7TOAPuRe4PXDsLAEVrq21SIeuAOvt3fqQ5wg+QH/OFuGN2nSv4NGdtzukKF9Q4d24Pe62X2CrwjeYEKUg7HekPyCulX+6tY1hR+wm+4ueAs9mgJ/X59AQ+9kL1hpkvZxF+Y8lpY2rXZFL+RZjCwX0IQVSk9dvMTxAn3t0L/1cElJ0F+MtPHUa+MH0IhsvOy5Ymj7OuP9KIygiAaRdAKeYB0Qh7TiIARr9N+VRPui1pDWoohxhpIKzJjJfSTuFJPIEPSWoNaRiKyKgyoFmhHlgUwtYT66QAoAiuv2YQrr2viKVaB10duh6xYurJPLEJcX+n+PEIFT1vzxuGIgNm2IB6zDci58lueEBp+1U3zpCKw1kXbHNvRQ6jV2ZRpxI7tyb0w+KmJu6N7obBeQtwacCs4sRMFPVuTT7wi2ur77d0+/s2I4I19+A7OWkcu8/C3h/ZCYtWCbK0vVXwkIAoSX2+k4Bdqy7kW2+rPFf/i9UrofTSiJ+wZeXk0NwZ3ZyGyvPN9pYqTfOE6yKpCv6e/kv0xzfxGvbe7oh1qXRPEK75COBB8gYtTecE7IHRNH6X6RLjHfWGMU3qR/7mJUSXpeQhfJkNcTXXObubkOHywz8WIPh8BO3QSQ8tB42X82DxDWTRXLrfoOPdMmn2qO4cvSSppLElP70hvZ3QbsY5ax3w0nOI35IvCxGCn7WH9iXkTvrcjxZHmSIvXl2N0y7KT/yB5bzyyS/wsNX/P603opRzwI6gnYGJXm4e43hRZ7qDgwBRjF0CvqIQo8uIVGd0zsim7uTpS2L59FFDZbIfdwgsgTxfRFkW+Bxn0okVdrYTACOPlxHsH+fIjqplIuvsdb+PSBTslMhNKqwfmY/K8353UdyHqmKh03OTWiQUqc2Tz2NJ9xdGTWw90jRuc5IfMNrJ55ORh+wjOZB+9cQx4y9aM6GxeXjH9pfc44fTR4SS1jQOWsqZTQ/XRlj8CF5TC3SGLa9w+fRGA9JGZ/73my4CKsmj1yNbV1c96azHi0PFR6xQurnVm587yFV7O37rOsHtcqzc3y2qsxqy6UPrP2IlyHdWmvmiYbXa88no1uU2HLqzMpXzajNq1sKf6HSoMelMY64NEjyCvt6Bw/cUzrrGdMx7BiyZ6hz6N9u7eTmJDRe+jsqF5ve2cKq4adzt1beNkvUshBjN7zV9KK61z0Y30V/PAWTxp0yhsYWZlpYYpC91KfWedzFLn5sJ5o3LrEcdFVr15l6lhgH5pM9MCAAjuK4amxQN3a4K61vH2roBuDpGwvc/QzWujDvGGDT8WuqViQOe2xHSibC+vAM1H8eaJ42rZpre4YaXFtaoyEZXKZu0hFSyuEWu77auncitHV7x8dIWmF68MJn1yRWW0l+RC/m03qspxLYcN4pFRqI8PIpolJkovLrLmchsjKQBy7uSxTSeyp4O3i28ooDcjMlQeIW2wFESlu3F5HxIhrnpaOkGbzQwOzPENTCnJUQSqduxwICBj37VVzg0clAMesuqYB8YxTFwOWGWI7S2bjmZ6H/S92P4d9uFuGK2T4eBSqjRQJiS2m08LW7XAWjApqEPEO7V+x7V7EvCHPgAALP/TK+iNhjPcrvog28ndAcbasOOggqRX0xd1RuXVuxYGsdLPBrq+Ig1u3aZw0ywONCNSiI+D+On7hDqc3h1shHCvaOvQnuY/sORml5bAXup5IuXEVwEqk+F+lIuWFC/r6th321ltCAmmr6VYBuV01P/ki0yyPQTpKH2miHBonqa1+Nz7paXSZ8YoXdhdHjLdvxdxJk4IYWvUgpb19JoZvfd/1Kus9vWa0+qpzYLWWgnm+g+SBhfSF4dacan2oHBs0dH8Y2i09swvnt7T9OrWrxuFmvEyFwxg9oGoRvEVOPdzdDhmf40UpTxVivp+b+2mN0tpSPe6OFHhcLi3TKhzdPFfrK3yrrVxn3+q5Ua600EAizkgZAY5YMsY5mlcNO9eVO5QpMQaKssS8atsHreccBW2Te/frWVp11IvWpTA0d999WJxFa7uPkR0zc1bHzMEhjbYRmEDei0ZRnubK6NVawnafLmvFYwOlWHVIBo0eBZgy7uJJM3jxn6KMZrcMx1GbZUz92+/LthcFr838m8UmnVatM4JKuLY0x0vUdns8md0F0DMIW2devRT0rTLKK7feCRxcyk2rgChzx+TG6BOZjJVrK0yJ9NASwdNwniGJcNp2+R8LooagqkXd0sFE0S8rPzf+QNwFUB6CnBRPC3lC9ctQeUFbcdJSHqNmMDC1WTbSBVwMlBOXumFxL0FeDhE8gf2qc+f3P+poJIqG98nJfhB1jgcxo63IvS0d969gZDigZP1BcHbgE1o6hy6Gq4PSDUYQrXOHSQMDs92Jucak3YrpHZw1+uLXtZqmbtNloSTLXl10Dx0XgsGUYDJj4NU1CqAa6tOxgmCo1zESYInF/qqcjGzcJpfnh4WOEoQF55s1byIQgai8IT0ujeASWD+MrTH1LY+bdt5oJqb17qlOVZ3pBPEAYI/GTxqNOZXAbeapZ+8QBYgyQs/Y8ADFmwQw6Au8cGv/2vYvaqNQ531c+7q90rkMJUIkjLZf1bQseoKkLty0oDKZPKhV9ph4MqVc4DeHyLIm9CZwh66+4959jydXtX1eQHTWCFbqDxpxTar1OqlWD8FW1WfcYTYXL/mHlcILvMC7hSfo4ejVXd2NS+epK033IeRYWwh/8onVw4ctyn5p6m9y+df1zoTMesG/WLoiRuB6yBA0Q18GxJvrcIvDsmIWUrrEuNoQONs7Gcaj7FKx/2RMXwSyz9QVV8mF4UykDx8lSzbuelk+Gjr0IaC+SnVa7ufEQqqYkjfnF765NTKTMwWfT9ncNRaT5k58o0vS0xbQM3tEs8DAmpiFkszw4DXA5NQcG4dy+Fn9XY1waDVAiaQyNFm3rWB2jAflh/pRGR0N18HKBzCJd2ZrHBunl7GKSOg2g0bDu5XDFX6cMfzfxUICg55PkkOfoRc7bIgs4gm5CjCeqthr92jFcyhWw6XA2cfVANNpNGVeyXafZoXTYtcg/B803g/AoLXbEtSs1BCzUPX+zlPzYr4z8uQonl8iToIdwXOygi1jrODBGmTYX5TKWyVmtgoF18tegsHzuu0R2A6wenVOwyAWDx6E7w3K337oT8g0FyJlTp5vT4FPJyFvHrrNJlDza6pdzQz3654hdcBh1FqnsrTelv6b1W33G0rql2cYcExoOz84vbv7tv2nlo4O5XZPamYcHGdHdsrIrNIxlZVuhqeWo/OrZun7JPIBhL5UG6Ex2Azel+uRRU+60D4ft6ITJMUmNV5AYDH97SXJLfIiybqd37dy07BK5VTxr3dGyboy66RrAc8k4CthpaazIEjSfx9MLF0VlnuT/6cWBsnYekeNwKBSG5eauZD8wFnQIxSUlso1NuybGkczkpN1Np8PZk35m7rd18SyoRDls+pbVu6W0T0XZBz9fMmeTe9qx8mNXkn6fhznyZcZWATSOIodhg5THZDtCC1zW0cj0SoUYmfQKYdS5xa3Do/nUrMflDi7QNlwioTkfiGD3Z5Hg3zBWnC6xcKwnknoWQcflFCCx+dW7vDPp0PQDnIJeDufu/4ah4qDR9UmM4xwTwZJFPb6mSQzQrPQks/DYGxTE/2eu2FFWVEVNR8cjiV7lgVUuqn9tOI0qy2VU8PBSJf34RUfQs7NwMZKvS51BQ0BKAq4GqsP3P//pEJfAnlhfFNP2jIM/vZza2qGj02v12TTPqlQJfk/BIy6KVx0dMxU7HqJS0l9+ZAaMO7C+N6Uw6Mqe9VuqltdPVkymmfX+TIOhGm3xu7XLP9dHXEUEvh0uXB0ujWdo6PsyPfG5fMghH/wHaSLDXf9Waosq+u29o4PfCbksH77jeGX0fbEq4B1acu2A6/wh7X84i2MvEFzLy+0t8OPqLKhBniAR7wyCR6kxzFOVNSbfQdFBcy6QOR9coYReaEuz2suDJWAJLhpSrYfBEWFHr8y6iDTx2QrxAwEbJpYCsI/auyUipC1oVZxr1lXP275sURFS8Uhnddiks/bbdFUCUVozT/8e0aQ9QvZEMsLwwvHLe806x2Hl+pKIr+m7h+FEpAE9PWrUGbJJIMFpw+yhwRiBSTmi/bkj3h5KHTmqMVrzgDIxLVzJLmfofOZ8AUqg4Atql7gcpSywbdylV9J1O5Jo/O4IYqhXObUahmPpBwDBiE6ACK2q5B+I0JCncvKrPvGm9t+eygGPgIDrccSgY0HzJijlvkOhUCV+fB66F85LvjuH54J6sm/XnW4/FF5TIpRizAoyPV1UkpKY8F/gmDEBzEz04/yI+LVB3tA4awQ4BeO2Jc3gyL+hb/rsIBp7kT2fbDQZSPPjtXz6VyG7u6UWYsxrogEo7KujijcpktXV2BvcZJccM/uIX0TJZDgnZ20WrvLFd+PpPtOoGzz/tom+FVEn7v1X2v3WWeKAQHFo1wAwQUm2zsUKiXALcwJ4232+imwjQKqPm3BK6e+GGAw5qEH8eA6DlIoDhRZVuU7Jy395liCEm3qic3d0Hmit1OkLhn9rXz7zDVq2K0P86ijesdVdbZMm8G/8MjuVy49jNoB/DB7Xc49mSGzfO1lOGdSE7RPkKPF/g8vCwR8TSw63UdmBIYSuXCX04DL8UkfsfNy9p9yT5Kpzh9d79bMIcodb1SEg3asuiX07Kt66e0wsBm2UaNevYAC/We5/wb0phhXx+8Q8eF66e3WkfLbqsF6STu3Mkhswmcwx+xL22NMX4tdNV2obTaNU2X+SSygoLT1c/ndKTSGH/0fLKGo5AkEmfmOUun3Y0J3VEaE7PAXA362MzcGntYvKDg
*/