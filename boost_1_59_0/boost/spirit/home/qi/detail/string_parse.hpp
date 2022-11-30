/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_STRING_PARSE_APR_18_2006_1125PM)
#define BOOST_SPIRIT_STRING_PARSE_APR_18_2006_1125PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/detail/assign_to.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    template <typename Char, typename Iterator, typename Attribute>
    inline bool string_parse(
        Char const* str
      , Iterator& first, Iterator const& last, Attribute& attr)
    {
        Iterator i = first;
        Char ch = *str;

        for (; !!ch; ++i)
        {
            if (i == last || (ch != *i))
                return false;
            ch = *++str;
        }

        spirit::traits::assign_to(first, i, attr);
        first = i;
        return true;
    }

    template <typename String, typename Iterator, typename Attribute>
    inline bool string_parse(
        String const& str
      , Iterator& first, Iterator const& last, Attribute& attr)
    {
        Iterator i = first;
        typename String::const_iterator stri = str.begin();
        typename String::const_iterator str_last = str.end();

        for (; stri != str_last; ++stri, ++i)
            if (i == last || (*stri != *i))
                return false;
        spirit::traits::assign_to(first, i, attr);
        first = i;
        return true;
    }

    template <typename Char, typename Iterator, typename Attribute>
    inline bool string_parse(
        Char const* uc_i, Char const* lc_i
      , Iterator& first, Iterator const& last, Attribute& attr)
    {
        Iterator i = first;

        for (; *uc_i && *lc_i; ++uc_i, ++lc_i, ++i)
            if (i == last || ((*uc_i != *i) && (*lc_i != *i)))
                return false;
        spirit::traits::assign_to(first, i, attr);
        first = i;
        return true;
    }

    template <typename String, typename Iterator, typename Attribute>
    inline bool string_parse(
        String const& ucstr, String const& lcstr
      , Iterator& first, Iterator const& last, Attribute& attr)
    {
        typename String::const_iterator uc_i = ucstr.begin();
        typename String::const_iterator uc_last = ucstr.end();
        typename String::const_iterator lc_i = lcstr.begin();
        Iterator i = first;

        for (; uc_i != uc_last; ++uc_i, ++lc_i, ++i)
            if (i == last || ((*uc_i != *i) && (*lc_i != *i)))
                return false;
        spirit::traits::assign_to(first, i, attr);
        first = i;
        return true;
    }
}}}}

#endif

/* string_parse.hpp
wnZm9IjH7eb+js54qo948Iehs6cAv5lg1Xt+Qd45aePWgYudZ+YXh02Y2fst/oU7xLX+arONJ9mlhvwdmniCer24RK3nYv8H6DOkgZSTzJ3MFzL7nc9+maODR3xmmhySduRmKV92ypHKqwQaLnnjSc53owWbaJjMWhaiQc1l8KNV93uZJySjWI/7JgGETUcjpTIjnofeZQwuUUCzDMFmOJaBegXs294LiLqXMG4X4T0Lt+HcFfdW0PPgfhPSu2xd3dGWLRh79pvWsB2Yhq2XtHsmf+uj22jECVYaM29xd7lN8tbt80CcYaWR5x36tGqSBr8r9Nikmgu7VZVtzpmPZ5m5PszbOFs72uFN+9vSeuE53lZxsddkfcUyst59r8k87kyvQnt5J0KCts3oDtLk6jrLy5mKNyAPR1IUKZojm/bNLtnlntKlX/N59IjJkDZgNcJzG57o3BlM5S79KeLT5zoo/kC4R+NFckQXz28Nw1u8SJobmKBLlrto28riNuXFfmoHb8odrTiq1ylISZeBNWg+42MtwWLkJnL9vInsFu3ePDjEfjPWcrGU0ppy5HCnWpV9lQb5rlzAZfTCVfW9OL1ZcrM1zJYMZ3si+ZIM87galdmt54NAnwZZ3fOmys0UwOOo6eEsJ2FnZ7i1oGFrG7lcsSewafBOtTvRbelw5kZh2hMmV1952Z01G9X/Z+f5m2IkZeT1qRJlPb4NXOvPp9nlTiBTflY9iavSqvZCKfdPYRelrk9DCRFWiRIaatdbD6BiDYMerIOCnWQzhWkM9+059GJZk83ieIWfSXUk7y5uoPR8Yj7HTSlOu+53Vnqbrnjd9bkv/yQcN6KTuDkwEP8WcXY/kH3pLFJpl9D3Ka0Xf3aGTq/Mrgvv4nhwLlMg82Nl+VIE86RES2LVwMNq2hDmyuGd+xvrLbbKiYPOT7c9scw5otYTM3tvW8bNYl7cRr5EHBgLaRyo8z0dCgbYMNGdMhnYq162Qo80l/hCt7aUtPkgbTcyPiPX3CdtvfgE3B2PcBrsKKF8Fs6Xh1fGv5NRpVRGUxG2y90vpLIM6ZBfuKw/MRcIIogIN4SGlxTHnw+dzik1553358i6Mmdlkdc5SHMulSefxGSXYFAgSAjczpZTwJlEvqpsmZrD+/iOJAtVQW4SxytwfZyCDbk7+605baof+hg9GyyysMg4GBtcpLgRIEKIfIzmEh4/hKwdOVwcQx5JM1RARHp8xxz6HqLUP654HL8G4+hdyDhpDc6R8NtdwHuxlZzcXd5LSJ5oxiyMXS6eINnc6rkeRzyddzPjTLsIP4Jtc7V2OROCj7MLdsHvMZ6CnsVfABEXawDrXthYVKJ6OMYo6fWJelxGP516TMaA8uw6e2httNaw6NzzWwZtaLVgVzdtopmuWnt2GWF8xLdIm+Hq3eiJlf7QJRs8t0SLuDOdVw6QfVaBaeum9dDeqHXtJxvOQkQOOIt4Pr6NG8T1OMcBD+vRp/J8YKgdIvZQxH4Sa8y3GHzE0Z3MrmTXq+Z84HI9lVwoPp/iTz35kOV6Wc/o+WBHO3m1eXUatQ/0UzjrOX5wNMbpLGgvPI1UG/KO684w1qx8bLuqPSAIbQ5+0bLvuNdbLb18gTMNfEGx5T4vupk8S9sI3mjaCNuI2rATfIQdseP9xBWe1zpsVm6EWnNau5GygSzZsFp/TLNLv8u3xrX2ipx9rtXb5TOGVdJeg17vXuhepiilKMeo3Chy+YKYCyYuXUeK2TKeMi5vZ21nbdDjZv3uLdrAlkzDtuvhLbuW4DGYITXo+bj+oH7nttNh5aztrGCDtMZ13mAdD3FU8zYgSAwOA5EXkZepDQuBC3HzXIAsEG6HPAQVMt1vBCDEegWIGFmzfo/5kSfdwa8lruWOkxRQnc8149QGNUPfdtvXe3ZDbicaJC4mceVUd4OZYe88P7bXS/W1u2HjE7W3gFVDnZC2pXYIvNi2JzsspU7KMqjnPvCcFXVENoOZymH1sEepvIenQEyGDmPBRnGq/3g2PMyAeTgHcehY0OE6sArDiLrgg2xKAh+l9UB8MjZ8nam72Xl1QjL1cuRynWk/sxwGCbWAVFPmLfBMYX2hugtXgIr2ePAbTlN0vEDyT8B5ZWMu9UTu0Hspze2lrebNpeSat3shhY4KGHy6ctSoB+m7KZthZzLXomLHZ8vny+HPi43d1XOOTA5GE1ddaWFmzUR81E29TRLNIc0r7krNsM1vl5uXN5ZPmiSaQppWXFuviU+PbzLOlj8YGz5LPtKdCa+vhPlQPcfTdEkyfzSbSsnvoegeikzBYRU0FR5615amUKR2sb8cvCy+3LOsunzTVNpM1JzelN7M39zc1NwcEodCTSTFk1pDZWEzIT8KlAs0qzfLM0swqzGLMAvcMRqtysOuZDDS6m7B4aW1cJpIzouOd6Y8kgV5XFM/oX/kt+wuOcfINbsOX9ybI6xlsrS5dMGoSXavdqcqlbkn679cLpAoS/3hbmn8hfq4MY8w4lSx0Fdy0+elC2lBRivHJtEmiqH/mq1CSD4WYDeWkRUgLOfvecPGRrpMqYlWGgbMYRiP2hVyIvvxRqfUAw/UaNfWxNvmotcmFXIiC3aR+vzyIkFDejGl3j5iKNuxB0p0Sp3Yje8/IepOJx1RQsHZzPNnIwZLoV9jM2GuG09ePPIh3pnfjoymyBkUx4lEiTreGyF5Gr0t2MiMjP5od2V7QyU+n8vpHt+c1pTWDB9LfEPjArrs2S1vEh4/yK1z5XQVvOxxuxErvym7KLsqOyOOfGa8V788240fL8hpjRYg8iK7l3FK2Z0Y/3YMMU46bpXrRRerVa4LtT1U3vvweCzX4OvT09IoOYTnoeGlxNIrR7yFnDlFvMnktr9Vz4mBOFS/+uHDPgfvSbMT9q2qN+/lKtHB8uemsr2fYBmBCrrsI9b8uTZ6T0hlKTZnkT4EGsUHK7I9tISR4stvToovWZkA/EE7sFvlHNlngYIrbYE2sQWnypKpxp3JtJLbqAglulyZpcoAsgcorELiQMgKiYo1XzGiPmeKoyTFqBI4dogvLulBJao3t/h25p19L9GeP8v7fWOivGjuF1xmen5kXs/FOmft7Q+E/CjR3ny7S8XvByklJ7Qgdmc9a+qYKK3F7q3TIvb5epkGPd4JYMFxJ24a4gBwYgDlTk15nsBCQS8s24l8BoSnUEP7I9YdsdfYpbV4wUzD2bBUSDAU8WlMD9HgavORk0/e66qah+uikcMiP4UqSvar+XIIDrAOPWYdnxpMzxR1kpPBoMZbzRBzg4xL0eTnHqnsSokDYCaJeeo9zKeI7ZQoVMJLDFRHcLTfVn88QMTJlim8K42QZ+1+DGb9oGi8y/uxH0S5nEWjmIU74R9lPxCH3v8TidpBUYIFpHNtgEVKtB3GP7vcZBd92uL1AzWPEIgVIwoFW/tYOOMr3FkIMsaz2iXt7nC/grNjbXv8cckbEJy6csihJyS3l7dPAFBrtctsQVt6COH4ljk3mJo9djom3AlzFQVnAxkSuxRyjVDbgmikgkIkbFaTyRR9LYXqPejz0R4wsNOOos+i3bbdjlsa1szdruB8WAveaCoDMFqeP603nIuJvQktHXL5acq/y1bsPBnQfUDCLlChTkgqxydEoZP6MHklTn0zf7u6QTefuV9RobzxRHrRFKC4XFqxqfSwL6u00ndiwVnzrjEI6758375kYCt48IeiWaLyvdtcrrd4Ji/iF9b18AwQRyPwUmaOhIOR8KUztwGUmdbqLqCLPbfnndv1Lk2Vw22nQHf4mOmUUaDhue3wKLPRBfPwoaf+Qay4NqF3Ef+0zqH8NPqOacQVv8lM4bYBLYCY5wLVK8Qa18NT68TDQPigBU+5zKjbzwylDjWabu9ZJMO+XnEzg2OG6Up9fsMrKjK1yDNh82m1db4R3b5w+kWQtaflhBRdo+pqBFcLLrvkGxwlW+TbeJtk4UT6eOVQengFbS1Mhf1ty4bu2SRsyuzu4Wmyz4r1jyMRNgkejS8vFy/8rS8nbkMXrhmOIx7LN/w7QzsXd94tJzOs1LlRbKrEvNc274rUF+9yz4LX5eCouJAypP1ChOQoYp633iOQoYHBuJqnNdnfsqH3B+pHggXXPKlIEmVBs1VNVSuMH5jDBYKFkq9Nqli8Uey+c2MMzqksPZOJx5+EkjEnlyS/Akee/OKRM7w6rvdhrSRHRgiepqpCeNLE1FSsTUz1majGD2CDyU2Bs5p80NEF5bnznXRgAxylJGUB9nQXq3pmL4AcDQcZ1mln9B29A6c6xDXTCcwJrOp4mQh2A0SoKFxtPk4zSixJrXWo3C6uQaLPS29AB33baIeAYzRBdrh/BmkcaigQLgEqDrlCCCww49TlvF200yQipU1fw1ZtWDMEuYBEp9idgIT0O2UWXx4be2IRTefLY9/8N45pCbRRAe79L9FPOlHldzHOVtvlS50o0J9Z/GQDNVlufh5Xf6L80E9esYswF2FECKot3Aiw7dBA9UQWhSxo9O7X5bTU/lpCj5Zao/QjWBJEV7mwyfOIvtwRYsTYXRo9yix2UJcKPOFYGZZ2q+Rvp7mbmIzisRriUat+Zqqw2rYTTQmJHVhJ/WZzBuEO0+RpN54/UZtZeKSWCtE7PS1G1YM+EM49RuQystU67i6NSePCz628Ne5c19pxaGIU32HOe3UQFHvkLqEBv4cvbHVOUF423rVtunxFrMUU7gzwXGsIlIXAxEaRdBAcoT12Vter/PKU53rZOBnsLH31gwSz7uzlvcMM5FEKhnxM6LsJOLZ8HFTwbxNUJIIWJYJzS73RbyJccumqouvM3gxg4o7ClS2j+jd+fkYx3iv1hmIq0YupYV6OlpnlfMBGschNqewTHptNY9/lQQLDNx89AKZ+L2Yv73xJX9syU3zUmJ6gbCX/isA/eQy8flZJ91QPU5+fvCsReavHxn/L80guzDXB3yQ1p1ckFsdwzE2aL0/HyUqxLnY/aMBgNaOqk722e+2RicVm2+dgidOzViXqOHfOlPChhnBWutK95v6b6E6IYI6TUYJ1FFd64AIbJsxpEB0waJkWmdepYIfgAhm+Wqaj7cTN3V28AnlU6aGwXNGT5MR3pn2TAemqbLsPxwHLXawrMwHRotGm4nz4x+RZS65frdoRE+zBPLhW2I4H80/FGwkXSjrivWr0JfTtSzNdkPvtReKN2/PJCqLPHN+pytBJGL54U1bOGO2h6WfkpJZO2NN6IdZnB1GhkGRNb2lc8avbL5hywnLGhHBj+clfW53Sk7+mYK1H+KO3efvqlWRdv8gLO4iiy6cKYoDndb3o2uCIgXMhnqbiaDJSYNdvc5nxgqdezZN2oIB7CHoveXcI9CmVQpRUlyG8TRi7kee7Xw9zjd7/Hgp5ZEqn/K5r0vdL6GHJqvv94Y0Gnx1YmHcEB7op1W4hhEkFhxapFqN72QxqdnBoZ1Hx8UwWLD6SCJs81PkLEH+sEAIaGw3ARqL+BolUPHZ6KDrwmEEOXTKry3cX6fZuu82ueWpCG6u0iJ/1DaoiVIOTtj4S4RrqWZCLx7JqJNi1XA/PRqj0fsydJhn+7OCl0bllxQfTz6foDxe2TekOYewqw9pelO1zLGujnFZahe7LqDdYqF7S9LQklW7dgya8jIcsYrKseo4Uit4mOWPbLHTa2iooX5unnWIeQvnC9nQVvqSp1dkptr69IF5LX3CiIgri+zp/sQztVuGAd4ds3l9RsRJHxALsj8HvMGVPylzk//ay2tUdee86fI3gJdIdyOppU3U+nDjxgVqNu1fDAP8q49KC/7o/qSXMjXxFY4BfaBh38Jt6euExBv+uOiXO+22HL+dJbXg1Oe9GKSTzMvLnYUS5TRIpovQ8kx7THJ8sFxoxtRYpwY9LJe4oL4++F/QUGu9Th1WbAIunKHfSKAVEFd70gkGjQWu4v5k71aP1ld5ERmyQcDZGeJP2sj6XIq8dsYdsDMK55lLg861Uwe1jdBLNASxiWaMKyMzubGalP5TsD+h2vB3mAqcLxULUqZd/Q1dlQpZn4Azke/LJsjHQBUJEINlIiSzU6J3lPX2nvuNtF1dcBcpgFucmuss8e1FaOX0d+VTYW4yRhvQwmjBLydHpP9C7xNS8/5THuzuTtkb807vInEcGM+RFacR19zo5GLV28DSAyBDjiiAEV9CtszR7STeqa/leLm6JgH0qnqlVpcHnET7cMiqkzKsfnLP39uo5kkDiwZtgVNWhwYePMjfD8MiD7VLei9ey+6cORzlFXUmLrTcOgSmpyRNb0em7lFPN9qPWNg2GicOjezWMYZK+UIKiY/NzRg+8eZ1hwzCZNnwWnTr1zKtDh43GN8fIfoZ6+zXTEdVSQUf1OioB0vzutTMXNWNtYBp80BeDlOVYcfEqimR61mketif1ZyC7IxjyVg6OoIHc7pyT1BceR53nMQFfMtMqGh+cn74o2c8Bd40xuFlAZBEflGpbFvq7YVHzo8T0cgZWiAUNqo8+9vGVSPdVg3CUMqM8WaJJg+ByHqR4XY70aNHoObAWNHNbbGc3C+FXKABX9/UdRX0UYWxeF2sAXrR/R3dED9wwobr18zbbJyl54+8pz/NiLNPhkj+j5moII9/lKiA5vwlShXV0HjOpxB2R7SWlMSbYDLqi2nAIR7cFmzT9qpRs9/UDjQ0v58bh4I7k2CQb76fnb3Z0ra7diyPnl+/Bo6hBwmEsKO8Flma2rCKkiF3sim2W2EmdOAHLuIxm2rE/rXh4bq0k2Rs0vuaSQQfjVnu7NK6rxbMTM5R9/XHzQTMSWjInQf1dEEjpx6SYILyb1YrKVmFGmI16oI3wmZkj1nbA17uDqDqUPFSZ7ise3N0Zqo9ansgKPlhdzMzrPkM0jqkDNQzN9Z0X2ixrNN5Ha+QuN3BTk5y7CPxP/CBjLM47jbihoJ5KeFDhu5fkIFFXgyuNqYnkGeinbgSykAoji5ZHTve6bfVr7uibM8yiL3Q90oKecTzqJKmt3UPGmiUzgexh1Z38tB13bcKcPxP50zoOj+GCFQME2BbP0s9sYjcAoAjS60ZTz+vlpUWZEfMT7svlrINSldcDMIGn0GYQb4ExBvZUZBEjgTIhEEtJ9CZQyKaesRxjUMnWThyhqkanYoheM8OAT2jyPeJO4TWi2MPXAXMP0oMiBDFRODREPebFOS119LGxQKprVnjhk04X//WbY7XeF/2kkqrsCi6rBmxrQWrQ+tUAhTPGyaiuHaFI+ypnB7wGeoHv6HaOItFz+fsts4Gu4o2VQ5mgzzUgDb2WEFr9hVJMvjkC+j39j8SthjR99uXaRS466dN+ncVz65G6N048uJIwqSQq6AYOb8cEAOQxjR8O7WfZaVyGgnBJeAddM74rHN1/W8Bf7qOGnaDoqvMevfXhDDHlQpKPeEskapHOjXLyRDIc7ecrmql3Z3bxkx5uOdoZOTnz/BaHsCCq/4p27h3GBW3G3hc0+hAbkIamWhhCOfSUB8/rkXjYcnu6CaG70ZzJyRGtWYBsAUzxrm8LTk8iS0HwCS3BCvdNVzPZ8pjpbagzpaDKdW7aRihw3ixcRHavkk80JE45fGuQeJF8fMO8gCXpUmenGrPuPBSl
*/