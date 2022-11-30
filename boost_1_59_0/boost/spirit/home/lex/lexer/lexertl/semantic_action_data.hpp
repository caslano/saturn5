//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXER_SEMANTIC_ACTION_DATA_JUN_10_2009_0417PM)
#define BOOST_SPIRIT_LEX_LEXER_SEMANTIC_ACTION_DATA_JUN_10_2009_0417PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/lex/lexer/pass_flags.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/function.hpp>
#include <vector>

namespace boost { namespace spirit { namespace lex { namespace lexertl
{ 
    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <typename Iterator, typename SupportsState, typename Data>
        struct semantic_actions;

        // This specialization of semantic_actions will be used if the token
        // type (lexer definition) does not support states, which simplifies 
        // the data structures used to store the semantic action function 
        // objects.
        template <typename Iterator, typename Data>
        struct semantic_actions<Iterator, mpl::false_, Data>
        {
            typedef void functor_type(Iterator&, Iterator&
              , BOOST_SCOPED_ENUM(pass_flags)&, std::size_t&, Data&);
            typedef boost::function<functor_type> functor_wrapper_type;

            // add a semantic action function object
            template <typename F>
            void add_action(std::size_t unique_id, std::size_t, F act) 
            {
                if (actions_.size() <= unique_id)
                    actions_.resize(unique_id + 1); 

                actions_[unique_id] = act;
            }

            // try to invoke a semantic action for the given token (unique_id)
            BOOST_SCOPED_ENUM(pass_flags) invoke_actions(std::size_t /*state*/
              , std::size_t& id, std::size_t unique_id, Iterator& end
              , Data& data) const
            {
                // if there is nothing to invoke, continue with 'match'
                if (unique_id >= actions_.size() || !actions_[unique_id]) 
                    return pass_flags::pass_normal;

                // Note: all arguments might be changed by the invoked semantic 
                //       action
                BOOST_SCOPED_ENUM(pass_flags) match = pass_flags::pass_normal;
                actions_[unique_id](data.get_first(), end, match, id, data);
                return match;
            }

            std::vector<functor_wrapper_type> actions_;
        }; 

        // This specialization of semantic_actions will be used if the token
        // type (lexer definition) needs to support states, resulting in a more
        // complex data structure needed for storing the semantic action 
        // function objects.
        template <typename Iterator, typename Data>
        struct semantic_actions<Iterator, mpl::true_, Data>
        {
            typedef void functor_type(Iterator&, Iterator&
              , BOOST_SCOPED_ENUM(pass_flags)&, std::size_t&, Data&);
            typedef boost::function<functor_type> functor_wrapper_type;

            // add a semantic action function object
            template <typename F>
            void add_action(std::size_t unique_id, std::size_t state, F act) 
            {
                if (actions_.size() <= state)
                    actions_.resize(state + 1); 

                std::vector<functor_wrapper_type>& actions (actions_[state]);
                if (actions.size() <= unique_id)
                    actions.resize(unique_id + 1); 

                actions[unique_id] = act;
            }

            // try to invoke a semantic action for the given token (unique_id)
            BOOST_SCOPED_ENUM(pass_flags) invoke_actions(std::size_t state
              , std::size_t& id, std::size_t unique_id, Iterator& end
              , Data& data) const
            {
                // if there is no action defined for this state, return match
                if (state >= actions_.size())
                    return pass_flags::pass_normal;

                // if there is nothing to invoke, continue with 'match'
                std::vector<functor_wrapper_type> const& actions = actions_[state];
                if (unique_id >= actions.size() || !actions[unique_id]) 
                    return pass_flags::pass_normal;

                // set token value 
                data.set_end(end);

                // Note: all arguments might be changed by the invoked semantic 
                //       action
                BOOST_SCOPED_ENUM(pass_flags) match = pass_flags::pass_normal;
                actions[unique_id](data.get_first(), end, match, id, data);
                return match;
            }

            std::vector<std::vector<functor_wrapper_type> > actions_;
        }; 
    }

}}}}

#endif

/* semantic_action_data.hpp
YDr+hfsX90H4gd7ws9IfTeufuiVN/1fDl+E/AuB3rW80/MkQfrhknsPOY+9jF7CL2CrWxtawD7J21sE62WXsCvYR9lH2cfYpdhW7hn2efYl9hd3AbmTfZDezb7Pb2PfYnewH7B52H/sxe5D9lP2c/ZL9mm1gv2N/YBvZU+yv7O/sGbaZvcD+ybpZGcdwHKfg2nHtuQ6cmuvEdeG6cjdxIVx3rifXm7uZ68v1427hbuUiuNu5QVwkp+P0XAwXxxm5RC6ZS+WGcOncUG4YdweXxY3iRnPZ3Dgul5vA3cUAEyzs003ipnDTuHxuBlfE3c3N4sq5Ss7CzeHu5RZwi7j7uWruAW4xt4Rbyj3EreAOhBwMORRyOOTTkM9CjoR8HnI05IuQL0O+Dvk25HhI99AeoT1De4X2DtWE3hzaJ7RvaFhov9D+obeF3h6qDe3IdGTaMx3/RSXedbva/eu/VVvqCTaXwZvha0G9DOo1UJtAvQuqDlQ9qP2gfH3dt9DXfQ99nQt8/QHqeje7/xNqKodqJqgSUPdQNZe7D5S1hcJSUBXiUzZQNaAeBGUHJQ9tW91Klbizy3qU+JUCf4zkLmI8O8EeXy3trRX6qG7D3/+s+u+G9t9Unt3c/0l1PRk8KsgaaE25hrqaP6lMXeW5jbldOsGtAD2x1WnuUcwYRsGMv855+NuZhcz9zAPMEsaz/vOYtOaDKzyf0JUcXMHpxIvzPXEdxrPGMpuuo6wWZ4H8bj7ce/rlryp/DgHXpW5LefY8xV3NOVWN1olVE6ltm4SdUxUJCvUm6zR4T/PiRTXaOtrq2c1+AEyjrXWg0NbkxV+wXqDmXOs60Nd58aLCW0geSAcYKukKIqNmxs99qAT+5rYA/w3T48djvhZ9gjJRmSQpI0CyMl2Zokz9P9RdCXwb1ZlXZBl9wxXKGae0DOFywBKyDh+oodHl2OAcjROOUmrG0tgerIuZkWMnBEyIJFooFLqlLHTp9oByF0opLUdK7+2Wlt6lnC1QelF6bS9alv1/783Isp1AyO6vuzuTv2bmHd/73nvf973vfXJGuEs20lM43fuTqQ9INz3f1ipjVF8HPti6o/WrrY/h5EjVPiIK1L5Xu4gTnbJX0sNxpPPwVBMRIs7h2I9LQf5dNVPgZ/4mkOslRVRYRprcNIYbY2IKrqQ+1Co/fS0ygsb37ilz3NTmHDf3H3s81tC5+TrJx0stL+3W/wD53zmu871Wif8/xxWY+0fadnY+ITC//MPeb3m/533U+1jTDzd8gvi8k+4i1ya3zsyv1zicaMKu3znGf9FwEFaDQ2bUmSNnVm8/pHpo9bDqEjggS6tvrK7sX5O5Zw/3HnzsvQf7n2HsP15w/rcS2u8bT9+74rl0JHXXHuwC3f9//3raH0Pb5zj3K/sXJ5/LTGXa93AE+P0Hw7ie5tn9/ZeB9h9q9N9pPx5O353uTP4u0/W6ODl0D8b/GeAFR+cOr76p+ubqEVW1emR1WfWo6tHVY6rHVo+rtleXV4+vnlDtqAaqweqJ1enq5uqW6vnVrdULqhdWZ6oXVbdVn6g+WX2q+nQ1UUvWUrV0LVPrq62q9dduqN1Y+3jtptrNtVtqt9Zuq91eu6P2idqdNaW+d32f+r71/er71xfXC/VivVQv18+rm3Wrbtcr9cn6pvpUfbq+ub6lfn59a/2C+oX1mfpF9W31i+vb69V6rX7ns3c9+8lnX3j2k3Q3fYo8nnvo0/i8lz5Dn6X76H56gB6kHfQ5eog+T1+gL9KX6Mv0Ffoq/Rt9jf6dvk4P0zfom/QIfYu+Td+h79L36Pv0A/ohPUo/osfocXqCnqSn6Gn6Mf2EnqFn6Tn6KT1PP6Of0y/ol/QreoF+TS/Sb+i39Dv6Pf2B/oP+SH+iP9Nf6K/0Ev2N/k4v03/SK+RRFilepUXxKa3KXsrnya+Qoih7K/so+yr7Kfsri5UDlDcoByoHKQcrhyiHKocpS5Q2ZanyRuVw5U3Km5UjFFU5UlmmHKUcrRyjHKscp7QryxU5Y3OPqxvf1j7S2vy90zIP/x+JF1t/2/p066ZFO1rdv9zn9OOVF1uPVzqVoNIhzhOVkMLfdZ6A9BOQfoQnoPDJaa91XC/exDX7FpJfifdj/VW8/Uq+pyom3uLUK97S5L6F6XSF32K1AnkeT0bhM6a415joJ3/K90CtQFnZFue67a1UBpW3KUPKr/x9Sr9yivKyP65cTxGly2nvJLR3Pb1VSSkblbVNI5dQVivrlQ1IWaUMKKfudEz5SCunKes417HAXljWfWFR+c4n/sJxV95zq/i7XPkmll2dixakuOeu+HnNA9bd3X+oOGf3C5y+ZN7+IeTk4GnBMf8NRUfDc2hvCbZ0tkRbYsKLOBmf/DafufXOfNW3+Xg8W1oubLm4pd5y6au+zeeWlttf19t8nnyVt/kwV6/8n32bj8fzIR//2vhNvlt9d/ju8n3Kd6/vPt+Dvod8X/R9xfc138O+R3zf8X3f96jvcd9Tvp/4nvP9zPdL3699v0WtP/n+jM9/ZDTf4ykCpvBsp1snW+ZH8z0ejuZ/aF40f75szT/al3YsPXHpf4f3fZoibNf4ZMzoZhEtul/EiZpjRBwf+qOI24yJeM2UiNRE/Tv8IVpF/XQKnUpraB0N0UY6nd5O76B30jk0QjqNkUETVKASXUzbqUo1qtMl9C66lC6j99BV9E90Nf0zLNq/0IfoI3QDfZxupgtFpKfaVhNRnkvbLm/jiE4ItuxU0cZVJGNdr/6Ww+ao2HWgewPt33Iz0A9IbvsFt+uazv6mczt43S64Pb3lEnB7estl4Hb/FgZzexH8kO2L5PthGNWm+0tw/y7n+VLn+h5cLweuAN4LXAlcBbzPyX8/rlcDHwCucdKuxfW6JrrN+DDSPwJ8FPgYcANwI/Bx4CbgZuAW4NZF/EviHs/twB3AJ4A7gbuATwJ3O/TvwfXTwL3AZ4DPAvcB9wMPAA8CO4DPLZI+2OeBLwBfBL4EfBn4CvBVh56Lr+P5YeAbwDeBR5z8b+P6HeC7wPectB/g+kPgUeBHwGPA48ATwJPAU8DTwI+BZ5w6f3KuP8X1eef+57j+ookP9pl/DbwI/MZJ/x2uvwf+0FSO8Wc8/wX4K/AS8Dfg78DLXA54BYDr6OHY5JZWlqhL2y4U0cnLhcS6Mnc73UaraT1toPeR1C+TLLKpQpO0iaZomjbTFjqfttIFdCEWlYtoG7F+vZeupA/STTTT+jG6le6gATqPBmktvY1ydBqdQWfSWXQ2DdMDix9cvMjDb9Vl/xlz5liGlbs2Go1jBtix+HOLJ1smWzjqegAdQAfRErrIP+jnVY7TbXVEV81KUTWKanrtkFoo5fTgfvvtfbRDQ6MsjdI4nUt5KlK5od/X+y6hd0O/r6DL6f10DX2ArqXr6V/pw/RRupFuwfXdbTNt29q2t91CM22XtF3mnIu8Ld69vOTd27uvd3/vAd4DvQd7D/Ue5uUg7+HeI7xHeo/yHuM9wdvpjXij3piX39XnvpHveYXPK73XepP+jH+V/xy/7h/zj/sn/Hl/0V/yn+e3/ZP+Tf4p/7R/s3+rf8a/zb/w+wb5blQZj56CdXv1KDP2H6kT92Df5R60B/uPj670ei47Vd6v7L8qsSffO7oHOfu/lZ7d339tWzT7G7Dc+o633Jju7Lm8d0281juz6ud9r2cvuMRpP+XZ/faPOgmKN+4X9/Pbv+j1t/+6x/+pFWh/Ut6rpaKulkZVw7QyxUohoWZLxZzBv1yo5VXL1my9oBdt1R7XbHWTkc+rOcPSRvI6UgwLhQtlEEABYxQpumqV9awxaui5WTqqPqnlKyBkqXZJFDpug1nRj5PUg+rAqKo1E7LcJnIdquE0WiwJPTaKqJMXOaY+ppm5vG5ZzL2gmshycw5dVbOsUtbAXQ4k7HFRpNFK8FR9ep1mj/cZeT2+Xh8zLNucjq9NJ1NpzdaGShUzq2dQSzdFvbJpFDRzWp3Qp8GD0wuuq9rMaIfqknCfS6Y6l5jMCKobeNT0KdvUsrZaBgfcX8sumczmuF6cyyZnNvVZK+Y4pWKhMJjI6baetR0GdUsvZnV3LGYpcB2UNXW7YkrqolUkGXZwvT6qm6IenjW1T9dQSldRz+SONhIk8+KnLNfom1RLz+tirFX505iobOn2ggosE6mdS8GG9RszwcwUs201Zzb6ZRaMoiAgWzAk6/PIC1LZca04pgfRkG2W8mlDy5fGhuUlMwVCLMc8b86syRx3nopaoTFmOZETXNOUlJVEnWkThQsVS4hipWicV9GFaIE5zandoY5UbDWrFTHgZTAL7ULOqBhl2yljMTn0Ybq8oJ0z+kumsRkP4DlbKpk5o8ii7JSqlMuQx7w+ihZKZhH3TsZIqYJRLo6h0ayN0cgvIHyabtpG9n+a6ulGzh4XH7tfp183xsZt+bn7tRJqJBwYYWsA9qUxci2NJQpqtm0aGHtdHc1rY0IwMElauZw3pFA55kqS4/F3px5Tp49C2HJQohKGwp52KueN4sRO6qoJ6KvJ3Lp6yLLPPBhFSDrG2IZ+i+KaINsQEYeC2g6xBmdozWT7tNyV3eE1qDiHtaJaEjbIrVmSamBxviOuUjSZV6cfcjwg3zBCudnZdEg4wsflLXVcg27lhUGQycI0FLRpl3t3SHiUYSbyJWu2P2epZ8uJEAYa46VPlWFs9FwwrZftcSaX4xtk5Uub5lieTeNGVhrkIWOsKFR6mLXZ5N+/tQwwNY1B1czsOKiJ9WEE1s3ukGoqiKI0DHylIGcArYeCGdMsmQNFWx9Dr3V+ULGgjegmzPGIMxejZqmgjusaD8wo2+8BUas9GAwuR8f5d4SDq2GTtDFdZKijJbMA2eLpxkpYzmO+5pODGKA9MIri+RKUzNism1YwMwmWV2OeUTfBdCDyxd2zRDInmIDTmgMRlnJTjvVcoW82ITo3Jws1TbdqVUasLDRDmN1gwtWSZilrLt5Qow5JihcnSLezMvHSNeksS5grHTOVC65rWhtdjXDYnobQlzW2PJW8hrF0rDeqQjSDjjEfXqexcVxbdnwOpiPUsizSndLuCiBE31lLByTvTjk20PAS5NrEq6XtLqcOhZ06EkF1TSXP60sO5pEXJ001SyhjYLaDQ+Ml05bq7PaIBUFTJw3L4BXI7ZEoPVgqsuTldB5w9GZSl1Vlwsir1EwbFiRreg3E2TSyqsWtCuXtaIwo5AertOYKQJZ9JK4jy4G2sGlOt+RvVausm0LTmgdgpGGnhJLJwYJRK86rjCkIzXX4YI2YW+FRYOGWgmBbLifBjbyQpDRrgXClDbbrJfaOWKZ4dRwRIjdqjFXY8RmZFuU2DrBxLZaKgSLPCbsEumRBLzouJ9YKs7TJ0nmZtUvFYCjeGQ/Ho/FYvCveE++NdyKhK97ZHe/siYdD8TByw/FwNB6OxcNd8Ug4HonEI9F4BPfd8UhPPIp/vfFYKB4Lx2OReCzqehgNRbCclJTrUVl9TaosnMG5XtKC7EZNtwDsTpPSdIgeu4aDJ3tCL3ZIPwOmB9PXZASgBVkNoqTbQVVFS3BD2NVjN4rNEShbLPjQBRTPC28RvLB3OYcv0/H7IDeLsBfxAq2ADzgE2AvwAwQowN7APsC+wH7A/sBi4ADgDcCBwEHAwcBhwKHAspO9niW4tgFLgTcChwMq0t+M6xF8DxzJZYETgKOBY4BjgeOAdmA5cDzwJqADCABB4EQgBHQCYSACRIEY0AV0Az1AL3ASEAfeAqwATgbeCqwEEkASSAFpIAP0AauAfmAAOAU4FRgEVgNrgLXAOuBtwHpgCNgAbAROA04HzgDOBN4OnAW8AzgbeCcwDJwDaMAIkAVygA6MAmPAOGAA5wITQB4oAEWgBJSB8wATsAAbqACTwCZgCpgGNgNbgPOBrcAFwAzwMvaLzeIptNPxE4SysUAJeWWnmK9F5yr1WxgnWCbXdGhswjuEA8H+kyvSEFXhpDQ7Fpq6zBLWlQmdn4fpFHfLYM0NUzQ5hKoMtiJiqUatkWk20e2iuCFX+uXs2/Iewrm4zhmzNSmTXM2Iq2oyr8FRGhWKMy83OAjPs4KFfxA7OW40B0tbwIKUd9LVgRyUC+pW0AKWjlVH7FfgyxVKrPzj7K0V9aDrgTg9ZV7YcZVuKXYFYqcmHArRq1lDo7Y39qlu09IEghddgx1gMuWSJbdT7JyJhW8c9KzlQzp2I7yREzTQRllsDaWnAS/J0FRQHONBkG6hsC+8DZ1wLYrMCA6A8SbzhAWyyZQbyJRSkcQmAiUw2rpWkN7jiEwSZXLY+TKP6zJqezA9OMjOUTBzRmY534gS7cGB1NrljoOFUTN2xy6KVS44sGZADp6QQrTiOJTwLE0sUZLToqSMscL6s85x7RcY53nrk1hmYG5L0uPjqWhkwgkyJe1ZBgwrOCS3wnMZcxI5zDA3gxuWDrFbhPPlPEtHlrtg63Jpi3Cm6+UVSjle+UWXnLIFOLIdjQiOMcoRnJ12cd4a1LwANMUKFhoAR7G5mCMBoiuCX8yZyMxMwW23dVcCndSNA27CoIZFarwRCGja9ctpE5LoBgDc4ADPqhTUJvsitvvQP6YKd0tIhnQM2M/iyIHjFAl/dTYANaoZ6I+InjiERJvaCAxQkNU9WZpKCGFasAm0m7ePwllTE8wIjw2erKYCjnPaIDACr6sg3NPGRlcUyKPBkdJUcC13L+Fo9CSPtTQczeEdGQbhqq6f19BE0bqzF2MJYLJBxwsUhOCZlYS/y9s8pzsYE4tnC+01CZ5jMhdGzBp9HpIRH0cn8syUcMzcrW9T1eYBFBSksIjWHOfXna4RURHCOjuEsjl3M+D4+LzvECGpkgzHsf00uTP5SqHIPk7BAJnimNwgSn9dyq8YcE3eSz4gNhPreFyFCFr8uHbkXHRugd40YnpodTbW1zAW8Tmxw7mRtKLctktdY7lKlwpYC+SntFpiDeKd46Zx7KrV8ixLKsw6hoYH22I/r71iVYS3rjXGdvlG1GQIMs115aiKejutONv12Ts1kc1yHLWgWRPsVrLz7YQk1BVquKsnGolFY11q+6rMmsz6gdRwAvZ8hRqa6gzJY/lqXmCwi5kYyM2x4K5Iz5Hm2e2N4N6JLWqW7RoMMdiWu6DJPbwsyrKHgtKUyhSefW6dN1ETMPOFss13YpBPkvPeLHVa1pZjUjaZuZwbUoHlmHD9FHef5CpiWVAVxZwZc3fDOdGSrufcgYd9wTDD5UnJNRXia7ERAKtsdhzdFf6GG/V1GJBrtCbEuuHQy7CRJCWFe3ZfJXZScitwGisC7CwWlg1iiEb0pq18Q7cmRTGhiQ0lza3XC6VJfRhyPMzjPhzeEoslQ7FErCeQ6u7uCkS7EolAbzrZHQjhNtLX29md6Ypsbd8wlBoeWpNY1TM8lEmsT/WrbzlZXXb8MnXtetXN6t51Vu9sFnKWz2NiS0+irzcVzYQD4d5QbyAaC6cCPT29iUA60h3LRLpiqVQ6sdVVveGNRcesD7PvsiWSiCVjqXR3oDPU1w3+M4lAIpIOB/pCmb5EuK87Eu6NbDWdytHO3kEb09gZqwRz+fyWSE8qEulKRwM9nZmeQDTamwwkkqFkoLO7OxRO
*/