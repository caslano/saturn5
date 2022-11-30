/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_REF_CONST_REF_CONST_REF_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_REF_CONST_REF_CONST_REF_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy holder. This holder stores a reference to ref
    //  , a const reference to value1_ref and a const reference to value2_ref.
    //  Typically, value1_ref is a key and value2_ref is value for associative
    //  container operations.
    //  act methods are feed with ref, value1_ref, value2_ref. The parse result
    //  is not used by this holder.
    //
    //  (This doc uses convention available in actors.hpp)
    //
    //  Constructor:
    //      ...(
    //          T& ref_,
    //          Value1T const& value1_ref_,
    //          Value2T const& value2_ref_ );
    //      where ref_, value1_ref and value2_ref_ are stored in the holder.
    //
    //  Action calls:
    //      act(ref, value1_ref, value2_ref);
    //
    //  () operators: both
    //
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename T,
        typename Value1T,
        typename Value2T,
        typename ActionT
    >
    class ref_const_ref_const_ref_actor : public ActionT
    {
    private:
        T& ref;
        Value1T const& value1_ref;
        Value2T const& value2_ref;
    public:
        ref_const_ref_const_ref_actor(
            T& ref_,
            Value1T const& value1_ref_,
            Value2T const& value2_ref_
            )
        :
            ref(ref_),
            value1_ref(value1_ref_),
            value2_ref(value2_ref_)
        {}


        template<typename T2>
        void operator()(T2 const& /*val*/) const
        {
            this->act(ref,value1_ref,value2_ref); // defined in ActionT
        }


        template<typename IteratorT>
            void operator()(
            IteratorT const& /*first*/,
            IteratorT const& /*last*/
            ) const
        {
            this->act(ref,value1_ref,value2_ref); // defined in ActionT
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* ref_const_ref_const_ref_a.hpp
KXdQOwlhfaDMnV1EeH/2SRyDPVl80ohNp1z5oaD4mUx7mdLgSpsqEPNl0kZK0gom6QUTYJ4y3FflVFPhAXcgHl30qDioj3qBk8Svfr6qCcv7UZEDfFWTwmlalVsrl0EN41Z7h+GV05c/TVVooaSCt1IG+lLvgP1Qqi9/Mq37gFdJrUwpj7n7LElavheI5ScBv9gFSAJHF4MjxKxYtrjt+3NU20wLQsvJ+dRsGrycqdmsVIw3kYYX03n3DJtWgI32i0ma3QD/N/b42WRG27fLQw7pDQWwKbB84WB3G86vjKUL5WfNNsv1EhtE/sC/Y6Oblmhnsb7f3HLKPSJ+VgBVW9VUnAxbfwPbS02OLAvalAsjy4j3HNaVN8YO40Wo7ieBCTo/0AtBjb/X9+eLy6kAf/PyN3Pr5y8o37tLp9dd1gmwwyEo2ct6ZXtmoD0yqtvsUv1VNMb/kTIt94h+IF98FoCKXbHPiC6iv8uuQDhuF9oT6FXGcoOyuCmeRFOcuUdijtwj+TPveze3vnzB/L27ao7QTM71Kh040vGlNe2A05q9arpwXtRlxAY9w9tpYOem3YUGmX5X/mh0yUGGvwpTNsJh0Nic0tAO6ANKxUNmFvWKoBT+l5zlG7ieiJ0XKhXzzvISBg8cURinvkwDMezPE6C8NgZjNCzCdkgkw7hiDqKRcTvKhrTbCceIL3u6DN5YnPvEcUN8LJ/Gi5ufwM6RVjBHK5irFdyuFdyh78cyLqgQzWycWC4xoz5zfKTNa5YVKMD24zhKKG/z4V7ir4q+bBWObzXr+a7Ij1w2ALcW2KjnO0Oaeqgh0DRpFMczGaAPhGJUK2yKZeoDl587wusfOJleQdXetIwepe4+clcj9hs8sG6BmvfqzXC70wjhXLw+/VuiP/UmwxKpT8vt0gJbfarXU70K5KG3u6evqPwz3+IkLZJ/z/Iyn9qkzAXFCGy1E9oNtEfDz6EwLbBZvNHdh/w8l0xOsDrFU/8hA9OnB7p7+pjxNpshoJBhAtA4VVxYL5k6LfDUJj3QQsJ+fw7QsRUnFbZDg5xocINnTR1/1kTEuPpF3BY2+g8olyTYNuqCI7BVV5u1QCeYsVJxPrExuUYbwq/4wl51qPhXVw9ruPvRQGNFxi7Vwk1wV3y+eJtfLVKGm/pfT0MAzpRsUg0MtW/jYZH7bu5e35Tv064O8k2BdlVN00vq9cLd7DK2o2g2NNzLf9HLB2XAmEbqHZGdDmK2zyhJHBZWWWWyLKVEJygNbKG5zilIUs4OPiPZ0agXBGnuiCvJKUjSyw4+I9lONYcbFd9UI3BIKzzYZ5xZtxiqhONmWmWHwOtQ6199FvrYgymRnx5K0c/2BXU11PeTavoExhl0u/vn1HdKzB/nW9ap/NhQnzJFTpzj03vEm8e7oUwh4WqM9NPf92TdeD18NCfcEs0fF4wGNqPAARO6DP+ksEv6SYkNlq/W41VHbhcxuYbx4Pkptghd1XTV0FVL10N0raZLo+sXdOl0raErStdauh6max1dv6TrEbp+RdejdD1G1+N0/Zqu9XQ9QdeTdP2Grqfo+i1dG+h6mq6NdD1D1+/oepau5+jaRNfzdP2erhfo+gNdf6Trv+naTNeLdP2Jrj/TtYWul+j6H7pepmsrXa/QtY2uV+mqo+s1uv5C1+t0bafrDbp20PUmXfV07aTrLbp20bWbrr/StYeuBroa6dpL19t07aOria6/0bWfrgN0HaTrHbrepes9ug7R9Xe63qfrA7qa6TpM1z/oOkJXC10f0vURXR/T1UrXJ3T9k65P6TpK17/o+oyuz+kSdLXR9QVdMbra6fqSrn/T9RVdHXQdo+trur6hq5Ou43R10dVNVw9dJ+j6lq6TdPXS9R1dp+iyXUD3EK5tDvMw7UbwgVo+Acp2Zn4fHSW98ll87ZOlabbKRcL7zZlM7TaiA2J2CCepnHX3F1Lmn1LmuyNTll8DJdPcZ6rpb6S+IyhGEzGJLvLO01Q+dhyp6rSp54iG80BrAh0VY7IyvUHRA/UWZdjtLjUyq+E27FkUdDcT1laiS9GZHeLTqceNu59BumguRc23110Hi4KL6YEYTj7x8Vi9fxd98iJ94nk1FXmJXhcTq9jqtMk9YeWfRAvUdjgTm8pKEZfn1XrKcfsn0lWEp/pVWrHFFYisQAs9Wrhe7B/QbRQXF9MtazCdTyHinn+X57Gd/n3Kr/y7lBnwBHaii/gjEoa+YQ1wO2zKoMvwf6NcWgH+mpbfEsrj36WnKQOoLPjZCbpibvYlEXRyq1DbC/3gFYJSD1AqJeA8UH9qgb4ndoFeKMTeri5WatTtf6c/Me2F7Un+EXPrxRslaTaQ+cKj4mkrZw9yxoiitAq9z9eVY+vKMIQj6CO9xAW7jGO5R7SSQ1BSlAfVQWDktRTtZmfba4TtuwrG2GEAI/UH2F5XxiES0Eh9yQT/NyQaqM1ttXYo5ZtdNIht9/N9C9//zA4hU98/XZx7jJ0hDvaVA08WAE8WTPDvCl9LMmg5lBflX/ew8kIkKy/YDVk0ILhyVJpKLSA5AX56qI0Fd+oF40jQ0Gd0wmEaHCf7yrOUZci52GrzT/Y6TKdmhdjc+guM732jb6fJURyRt7xUAjyw+2bzWfBFnUEjVCG9TtEo5xQepUoiBXem6SzR+ALNVQ490Bypd4Ol2akXEoW226k9bSu5cpfyAIHHUl4EWY9bSvB2Y+Jq1q+2V0ADCzCM/U0qYNvFsdFdRkXz+AxvPJPY/zdosw6CYMNRtrhifJcBVySRz7+LNPRzTOKRsIdpJOzhFmom1F5/uZ6+KSHOpVlLwU7OjU79LfFaMZsfyQPJj2HS/z2bnYKkG8EgrTMX/MRusyEuA0F+ae6RypRo4Ra0L4vWTnFpMc4lx9XrdvEatJfpfNwwxfDG1wMtvvHHu+Ia/kvXI1yJfGDnci7zxVtp3QaVL/5BhesdjE+wUmktlgbFe4PttqSq3C7Oi4Xwl4+dtrbZvG6FeJMQU92hQ/1xNlD8dbYJ9+3i9/H0hKGrPj1bPwbLwumTtYLJ+nQn7Aunj9EKxkRW8J7kdMDh9An6sKDxCIxxotPHMWscrqHBnE6SKhXh1grc+nSvVuCNTh/PrPICfktCblCfPjZy9yjbAq1gLItQFbD6rvsCA/16kTR5KnPpYTbbGcXGiUFt5q3wa6Ou1GpgGKO9wUZDT30DDxr+HrU/gTXvkcfc+qw7NGkmM+tOjc1kJA8st1oIIw/1FTjVQTDSy3kW9iusuX4ljwdqpTSogO5o6gwlSxj/5uUVheo3scKGaLyVIO115F4Hrxnmibqbg7rcsebNMcvOgvgrPbzS3AUP7JZbKfp0bPwgphObdIlRvzJhn7e+TciO4l6uALVXtL3NK4ATRfs5fReBTN1DWaJcQtDciNH3ifMv7zJ8S13KVVSnb1GncqlvaZaS6lMz1PNI4NvWfsrcEJGOzb8jztLRqLEuWp+V5d+vjKKsxCIHGnMC9aYlGu99k8AQuxzvBuAda7jZ22QiW6AJtaTJdznoOpfKL6VhQ6VDmjXIHFzsOwYPoTRamotYTGDnV/oWuZRiPY97cAu1ijtwI/aAjMUuI3P3O0O9aMtws6hAdeQrxwxZErF3I8xKKflF3j3PM181+9RRylRs20wmGMAuyCJa5uOF7Uvi5BctUi72TWRO/lzfRLbkGEZN6c4bY7Ol2xq4SLD3Spom9w7Mdw6b4kORE8Rr7VyMepn4c7slTMHhPGH24dMN7qIRaEHDU40AoSejEA1SM8RKyt4gN8OAJxctU9MkpFAdet4Y7RXYt0hDEK80BOlHNXqqEceLOiI+/kJ6joJPTB+bzMgDTjrX6eNNG+UGuR/gkBDJZg6OA453tMJWaWVGcIDjGq1BrbBd523OYq1ECI/Pbmt7jZql8d6SNHby8QgoCwx+ik63a2x6wDMHCpYHzJEnOf1SuTtRaS8tLQ3q/IFsAz0s5Ac0K1gsIk+QzPAiklIiLyJbylnLkyf2ZaGl/1uZV1KZDTUYPh5ZDBo7C5ezzwaLeJZmiD4eZ09Nrjmsq9vksF6YNKzD+Z4H9E45oHKQ/6/DWnctDevbaIoJRjAiVA1syaApaG0bemKO9CzKZoLQmSNijoU1wonmBOUWnaOBRuKi9TS6X6XIFZHi4w4r/X3qGCU1d+/UWEru3tNH28F2gEljXlpaZFbVt5ZQsWj4da+cfRPZZNIK9lRfBmvGGeN893Z6qs8FY0HLz9T/mSsH+j+xqs1U7K1kr1J8jHooognMHm8Z9n8RtTAmD3NgZWIDX1+UZVr5l7O98dzIFLAvMNiQMxCd5gJPlLSC+8v7wXL49Rl36uFGvSFnpyNQLyVj4KHWqNNnJWgBEbuNONolnzOf5nsGO04ShaZxpQN1pkWORjtxYAOsmbcXtpibpIXNxAk5Yv3MLdx6GHTLRmTb5E5DhvJf1GJ74Ki/G7veK33LZiiXibuFJExA2XHCZJGgYEgaZfDmCW9qq+eY5zWHWIQhivES+8LYCMetwfDUhuA4SUMYaHUQG8nGunq4xRHG9hKO35jIGcvinRM5jTj/1ZDDtMZxLH4wRxIlTW119BATae6ic2Va+KjI3g2r9xBoGTfFu0ISNn7POE8MzOBNdknaOFNs13HD9wZeetZsw4rj3nmq/8j36KGnZgNGYiJ07JDBDmqBQ5J8sBOR9yVlyAtKvy3WOHy68rhJkfShb2an2mwhePiF/mBfkLm22RVgEZlXkOVIyI/yorRK+e1KNqtAMWyD8dPlGF3ksPZzb5mAFK5naqc+NBRVD2ITfx/KZ+LNyXq4uQJHHKNqa+ItMyhTXQ47UTp9IptlsGmEjcc7h+dCImHj/SBipZnGGZ5vug36BHYexvsEoxkJniD7625zqCUCchQelebXReZG876guKy923CEj+r7QjJNnPi824jwFPCGNH+9T/z9GPGdXCF7HZFVnJPhFTdd02X2GOz2LbnHjdhI2VXuIve3Tz8VmZXP2IzKZbMKIqKlxDzJre451IcZPjVbySeelHfKlH4i9C9sWsWGApHkyG2yMeJGJKaYrJ2lPVwJ/WJiM4tbwvvfVx83RP10YoyzbZWuuguKiRn9awGfjSFRJ6+T+IGlvoJs5efi06Pg2Qs7xEwwtEuyIaqXil2fdrEvn1J+9U2EnY5cV8m+AjtELkECduYuzeOzp0jyYukVuoKRneOYc8+7H88slFx0ddwLyTlX88kEMWQ6s+xWy3K4ZTjm5fTUMLUoyCapYu2buGV2l+SpQUFx03qmVDW/t7HJvF7lFvYYccG7lnvNk8Pg39swFBDnIY1Fq8bp6Vq5u6GAPdr55naqC8VXn5p9vq2a+1wKYefgPyGiK/myyzbqMj1NLJY9nvqA7PFFiR6fS4MQlE5XxOz74r299qp4b8fRrbikQKpKitHRGwNxHyKsOr/7U1MN/04E6EML94pimTRe7KAkrWqOVjVXq7pdq7rDPHZRdadWVSFu/gzkIQvHMkimwXZath7IgLLeKaL8zutvSD42lVd73JA7arOwu3Yzdr1G6TMnVdojJwx1ZFBc6eO9MuU63iuLXarPnBDC3pu3KCiGyndr6F2MqJRTPt7EWSfoe0R+IOHCi2UuHCokUDugLIoWZAfFL7q6jGjBGBhHrcCtPEmocOo43N54FLdO3JZz6ijcFvMt553Bt27cTuHbIG6vptv4WURMfewuCEIOEkONJfBveKKzy4hUsZRnahvw2aed8Yrr/omsTrrb34m7UXS3m+9wqP0vfOemuy18hy+epzt5SLEig6hL3ZOY1/fyaV5VlvNO0CT8tvU7Qi0HK781RaKgGFxrEfajcO+Z18k+f+rVZTJyzb2ArYUi9AnLz+34+s1Vx40KnFqN1nTQM44CM6jt/JhX5uWV/Svt5qtoDb4Iiutb+dUQ8zkaRV1i2xIgaaRYeOjRKyBR4SW7SlwCSkU3Px0IbVtGxbQsgkwvVsY+cdmt5kmxYOSBbJtys9jammjiqFUwN5IPRXCzuo+JC3u7lG2IznQFxcQzGjCUGqDPWiiabkHp4g5ZpkCZjSvZ+M5BVU7D4bQapKLzYuZEPp92Xp/zaYnXV/JrxWMmRWe6xXaVFtWRfK08u6EgK8fGJ6xsp52w8iadsHL0Kx/F9ynw8DdzlDOWvmrmKGARPYoZJRCOLp2j9xDODW4SdyPALjcaaz3vcnTyqPl0NZ52iRtulG6P5tKIAgc0A1aun2odxGqqQ/jxhrTl9Hr1Bo4Ms2E8/07g30n8C1YouiMP9+dpC5zaApe2wK1tCPLLOfw7l38R1j66FjEpCZ2t3nAHJ2IuxJxhDlupdHvLMPT57wn3pkVr4bxSy9LmOrW5Lm2ue15lirYWoQa0tTjYMi+orR3LT2P4N5sLzOBfL/021I6jX2OFzbZ6ww/jLZCtkVYBIW3DnZz0FCrasJF/4bOyoRY+VeGqVWYkmqDVIiKIVuviXzf/cu9qZU8V/q3gX/ajuUc05UnUysP6+Q1x1Irx1GvRUOtIZL2SHhSTx6fZ5pnOf8fSCMixYoDclOlg/5e0Cq7fesoQP8+zjDaAW1fxIeCAV1vFcRgCbm0VE/tAhjwMn9iPD7h0r/ZLzh50ab/k7EGn9kvOnue2sid5x0lj3qbQxb7Xe6QUnSNT+aidsc4rd+mH9Uk0IwryHnCiPPYlxIdjTyvxSismmS4DDpllZp2W3LfUhIddxE6qMZQfF4cq7riUkMOef2JLGsRHOo+SDsDYF7dExejuWj5nNmzVJzjyepHhMYwBjZFPTq3aa/NIV/OPtCJbun6u5SeYXYTgjNZ8eXTRDM6a5CnVra8EcddqAQFwJYBGYlTWIXLBrshraI5NGaqvkjbrlTaWJhCBNeFHpU9UZuJZXXKbVD+s64DKTWLOJ10ymk9hsbhjWo8xT++ROCfJcW/F3af41Flhe1EFVbVSY4i2PJzbuLnqQNMhelA6ktoTNzYa47BC1VMPK4nfmvXgScPMbPXVg+bTO+4Ayt5f3jbl6m65vQ4PX1DgyqFullbsvCxUF1XsS472peZ07wJyUVKMNLpLwVkdo8BJt06+nemiW5e8da/61G7L44B8ylT9IUCyPU1/CPBrL3DqDwGiLy1w6Q+N4Rv3qpOwWFUDRBhXLew2anYR4ixwnYhNiKSlx640P0wzC0IB8juXVZJVgDNS4EyPR2GTwbb21AKr2KVT/JU7gM+oUdKZsBzoPbWcaKxDvHq9FigCSqi4f2vFbWxDopGZgcMFz+M+7iiCVzbQU8KbUtxzslpqGU0XJqL5HZWT6k+O8LL9Y9OUI8MyBxlAOCQ3wB7CBuPbYby8gsYj01LYxCYRMDCyA6jQpv6MFxh83EtH3rCGpa/PIYF4LZx4MAjDM14QxiyBp08akR0SznN1uf4msZsNBh54D9TXIjVYavwaeFdfy8f/9iqp4vPSPhHOeATcySPArbLWkCzba4EgHz5w2YBdEnEa+xRGXz9bAaPnNBk3hzqRLxGC9JeiTNTZQE2vZXu1YSF9B4hbzg6QO+qAM5SzM2hsw1MRV/EIx+6UddiT0EB/Vjr+Dl7YLYd3cH1Vqh8WyzecMnRJSiJOrosJSsTF9+hsVGeCEsE9
*/