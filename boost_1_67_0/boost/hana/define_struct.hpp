/*!
@file
Defines the `BOOST_HANA_DEFINE_STRUCT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DEFINE_STRUCT_HPP
#define BOOST_HANA_DEFINE_STRUCT_HPP

#include <boost/hana/fwd/define_struct.hpp>

#include <boost/hana/detail/struct_macros.hpp>

#endif // !BOOST_HANA_DEFINE_STRUCT_HPP

/* define_struct.hpp
dJ6ghv2azhtAzp0B9pLzF9rzGvpCRblzbUEXzMZrnT59cz3CfKD1MvHl8mWGZrWsvDpWXl5d4u5dN8pMNCHKWrDS3hxqK682SOYVobPG9Z/CBAVprWYUDxYP90vLm+Exi83oLXNaSuDPTPQBLLKRzQBPXJ4BD1wjeL4y15AwGbXICtO2HRXsUtpNmYbNr2Mnel7FTGgrCG19B38DBulq/K0zSFfi7x0G6XL8XW2Q5oZ6wegUW/cmrZ7kzFCvKSmEerkkF+rl3b3rebA5rBR3Yt214sttZXXckOttMbIdUkpCKbE1GR5ifyIqtmfj4hc+QefEMO7abgZL5CGDgXZJb21m1fyGZq6ar2tm5fwdzdzOZrmafwi6zLdBp0Kp+esOQm+epX6F+1tx3kOCLTMYgnbx5eplBvhTvaFZ5v30BoSu3hCDFBhdrFTi7l63lyVCigG3tajBpd7gfGg/b8OdBdYEzgDwi/NMcnGoTx3ZBThtSzUVWP/GZKLxydtWdKf+BqXzMaSQROsWQ355mHKZNo5FjNMnGkTQpvNqwWjBMFjnMa+KRpr+cZNcVJrSjJvx0JoYqjGRt27HjwaS/sF1gCDNrfnX9UTKnNnNzCy+3OfeuckCY281NAOIWcm/aV8gvmzGWWjwUNSGOjsvAhZIM7MJQD8oQIXvRFLPIv2HAf8y1wAN2r4j4LFdILWJPpUvVvgjFDMuFbNsx3ifq9u1G3zeRaCOYIaPrVT17oR3BM2DSniH9EUYT3Z51YVvgCYbSZoKRhFl4JJmtby6Dkanus4APbZLV4B2cIgd72reI5jb4ssm8WVbKaCIisMmPmbRTDC01QoXfu4+AdW8YsdpmOfBI9OuCsf9AKhS2jBsEMG+uHC/i5Owitlm7Dvkfnv9wliwug7jVS8vdiXCXe0iFi9dAjgNQvY6Bdrw4kXlele4vTgaIY1Hcd05V5rJuvUxwUM97C2yxM0Ry1aWBYNii5Q9aWRIcaerL34WjeVCYNKtppGVF8naLI52X9cTHkWyl9CwaaQP1gEcZ3g46CDnFnv5hrsvOIts05sKhlF3YHG2F8Zkxz4FJ0jZ8tj/SHTp19gbJsZ4GjvU+VyfLKKpK2cXdCUzqDpIztN0CgiMrV3KuovmMV2Qjge0qGvYl3aahI7ZWgTlJ8fNGAKWeWe4C08qYU5wGutT+l5SVBj0Li0ZxernjsRSq5QD3iKvXNepqGsiBYut4EAKPuUHF8w49uOfsXFMjQ+ucULlNfnfdVqVrIpP1J8hLHAsW4zofQrKd14dVn9W/UNIS6mSJWZxKnWQgv57wKfO/nX29VZ2Ap3Xx7C/M7Fgi8Gvzn4WMoBi69WZuQCPMHvklWEM0EPqzSzAMxMrwWeTupdV8MzojgcXoAFqlbOZwHy8T/bzyn9+Dth7BCCDV/YIVFnqYbuVP6x+D0CBMfsYFAgkPDwdKdz4uZnOn2JjL/55WJ0cWhyPh56sjXloR69FOdhyTmUV+ezmbYDvChbHff8V+ZLAKnx+9e3kdBbwVaqzX8JeevIxEM081T71baJMF9RtmtIGjOcfLzGe4JecZB5rwmy9qwDN7ETZDdbzoNlYwMqW8DHvS7UgeBa5PN8Say/CpVEbrnbScb3vIIa7ga8dJmX+fPwiaHWLCjjlAk44JHPXHFp7Cw62xQd1rBUG9bjyk3NmOoyDtYxKDkCoVWfbsRMVPnazAx6gcwCoEv5W5Ib7sZwhaGbGFqMK9g/AoUMwyntXasorvZoVet0+maCuFedDI6tHcK/2+HvJyDULJ78vm/J+z9g7K82dBBDoN/39L9NPqCoYDsC8LiwCjxPGDyfA4OUJj7UM6JnwrL57241WXAkCzC1GzWN2VuHO9vPzac1LJ7wfCH+jRniPFT9B5X0JaY5iROZ0Y25LOVFabsyTG/MjjYXK3GOaFMLE4e7pxQODQUsAhHDpbzgDS4EYAvvkus9ijik43T0AVMwGKs5CDpPbc9XZNiT7zX+Cv1VVLcYq9W34C7+yB9iIgv6eanRv69MUtk1cIvKzFbno01oCgKRAXD7yNLTc23g7nYEDvlLwUw+nIdeoEyI4LaDc/ymhDeXSR+XG6Jt7KfoCHF0mBKXv3nNq1FPY0TUWsgjqPIZb4HHS5gymQ8qis2a8fPTc5fQ9X70EhvqwBI8l5mIJTx5OpazCWVVLkcASn+xBO72YrRDIHda8YXryKQ0vQd9AHK9EiSvFdSVdIC0kkLNRSpNmEsp9JIn7UIrH1KDyLcAcacoSTfWNEwiaY/hf9b/5r+p/Suv/vK/uf+p/3f93X/h/63/z/5f+34M60YlmESCJ/aGzmkp+J4dahUeyUHOv3UPNWSY2xU8+8PnXtFd3z1R6XzOpGcwv6MLvuwmThIR5HDB/zERUVwggdQbcpwoGDxKbNebVLq1kPUhYEOU8pLby8ItA3YBO3SVA3W6kbuB/oG6vp9CYpvCuuy9N4TGR9aNAfjx3Ik/gNIx6KQN5gjsNPEEIK1f9gTM03j5lfgJ63folevlp9nDUFqjuRNDCPE7mhf7WQndbvErrx2MKSnAncC9A8BpyhcE8aTFqgX7cnqU94VF35enfoupic2pJ0+NqvKrt0LRAr8Y7Ze22GWj9NebLjB/Fo3E4FcgePlYmqHLAUjB05iTaPbRGLVfYE+YHQMfK7YIcyBGfxxiEDXxI2WMVn0+Euri4YpI9zvghk0+usCmfK0CHgBMQL+gPD8keR6uN9j8k+AjZUwFnqXvnupOoGRGNieeHtXboFDFbbpc9drbKKQNJa3kZrIrlAhoKqyxyhYXVWmWYX5fbAJrssbFVOfEjpkq5Ikd5EFqHNlmtg7XrOKitNtdeprJik1wEiaW4lrln3YmmKRoUpyKwiq1pPBIeuwMR5ihA0rzIaxkf9xwcd3uGgTukzPjMjJlZ46okB1WJncfMT04BMbxWcPPTaiSnUjucDrl7MbeEB8KzGaxUeKag29WNfbyMLcnBbs1gfjtaUB6hpja2cUH8eAYQHEgdimcCteMjXCzvz8RNMC74SYn7rcqDH2v9v5UHKHcIFA5Fr7f9HtYoxG5Vxef3hIfHpLH1ftQEMUuUInp96BcDtWZTrOVtlnNmnzwPPcU4v1I6SWFJNK0DgusNKg+luTfAC8RqGPld15OcD+MB1usQwFCjts2s0XF6KGLLgVT0FkfBrot/nOFKBVeBS7gdievaA4Z5hSNW/c3zZ/ayPpaKH7duPmwwqIYZe+DlY+s18GiYAU9CfESAtHYB4KutWUy9ajq8lHBvuhPrPmtqwHkW7LUJA5ow4iCyFQ4gfqZfKU6aDZNEEvm/CllfkIHEPp7FY95MoKkcEJDDKuyxMqNKktAo1LJ2BzA+ML34/P5QDxdPmsIq8H8wy93obL2qVnnvKIlqzPYTpGul3OhURj+EwcWVKrndER5uNbMB3LmI59E1HIH0FnDmQbirpFlMiM6DBCE6a/qByDyV9nrkk/hFF0R3DiWF+UwolQUW3y7Qqkh07tCRqNDUOH1nRKjXeoVKFMMXVYFXBD3SbXcNut6WcOXDGp0f/adypIdw9T4hO7kSWs5vx/C8FRreqeUNfRDNuvrA9IHkddGdp9/BBUxbtMEwlLz6XzF3DIWTsZVCtMYA7Wc1QPMY0rJxezYfzjQYHoHebcxYEepPlUom1TBZAUI5PppdhWCt21YDQNeOqOFqXB3PCQ+hIZRTCzZ4lmAE03xxdGd0P/R6Qaz4upAqtM9nWaXs/c0fYBtyFhvcmHFraCC1lL3hGhg6JJg2f4wZGzNWhfaklkPLZnTLpqhfGu+oVaeSbegI9t3nB9/egqquko4+K7X0nR1rD+kDB2KVywbdn4JPapGm/c4ILoGj22JgSxx4uPvGrrH3lbQg5o7XiLG7MOxQKUAvC91HcX1VjFWYcGtouEv8aXdV7cqFe9kXtAD00+6VC98Md6HD3cYXDCczn2H7Cw64DoRH4bUrmcl2kEJg9/Pud8XQBVBCbo8ghj6jNabr3YPyWmduq+DaQ8H5EVaBy89OblDGKaLcWeQehMxyipzk4d6wAHBwH7eTnWL7YqtdauhIZvwTYGSOO8m9Q+ofg5t+UOkIxe9gx+OjHHcUJ5jQx5kxC57FAXYUQ0sxBIy6wu4+BSgUQWpxrdjxW31zxDZi0G7t6Aquejn9m77pCygN+AEAtJfACOe6gcbX4JjF2o0bM7yhvhQtOyatAeXD82PLoeAwGd3n1i/Q46k+OhJbq7w+XmC5+9w6heZsmBK5naHDmb722bS66q9VnrhA0QMHNJX8B1ptrVUi5ynNDnWT9doapiBZCXBAuY/WsC3JJUiNcL+UTZUA9SUXiCmS34zZjKEvhPEM+byWoUHw+QPKP13QPjuL6yglVooO+a3cCW4/6lTuKC6D2MVwj7bVrRDRdvt4CeUwz+0VJLGpvmFshw4yFrwWdI0/pxlu/GkCf/sd4aHgFQH2PVTBp1utrPDRM2/JhY9CAsZGTzT2TP1eB5lZ2mSHO9PmfURKjBwO9DT4jyZ6GlUBTR8tn93Rxd5hZ6QFMC/hzuMPMND07VrlTVB4Uc9sqAEFLgYPj6s63d/x8+ARV0XrZncME6wcaS67adEDlk0ZrERI8mwvM1BmMMlKeTd+aCcneDkT3SstbZfhnMswPmhrapSt9beDWYaXfqBzPCU53R4aoug7oyXqj1WcUB5CRCs+Q0XgjjdK6RnZgjOy1Y7u9eJjNF+jbmbGStXH3z7J/psM77qvhXcFwvskORme8HXwDlz8OniXI7yfavBwB+P4mRvL7cgI6e9DrwErE41jW9om99awkah3dkd/IFjeckXB6TVObUs1hiLyKF4Oeq4XnQHF86dhdQyrPEherXQkhtU1vtxFVvpuCUZmX7ddb1VsgEkV248RjbXgn1uVtl++rzKOmglmsO8LyXmsSoiuxFce3OkZwONr3QNsoyDdr/HQel7i5Ad5toxfVMdLGfIGPjlj0XyJlxcnObA1WQPPODduTJlD5QFKb3IayH+EI6uYwwKgwxfdKkhBrUQm65WXCsnmWkUtpi9W4Vsd3olymZzthnI8O5m8Qmv9e1rr8mK2VJBLBcBVXjmOi5dPZrGl/KIcQEcAdMAqX8rLpXy0yhYttUX8tshSFHJr1Gt70fidATGs0se3ePdGXuzAzwwxtajJJoY/pANb7pR0LwgLFO7ol2ZF6mwB9kavx2ZQ1lxDQTAimtTKrEV32CQBXICi223B72q/MH1bI3fYfFCjBGr8o16jwhbx2iKNNuYDh+sNKKDYISe5QWsje0Ibd2MNs9bEZVAc23AwAj0PQbIaFEt20Z1irbwYXgZMnbyB6U37hAltv+IkSOmmrXrLJmgh0kT08Cl7DpvxmDAanl1N9a28V16GQfS7IfdOGZ98jQ1pR6R6grzqxjd98+csXoqTLxW590ugR3k8PLXpHAjHcl4uAUeATyyngIlsoBRwCniWjc2TEgBhcJ8K1oMqgmHeLZUiuXyzO4aky9kJQJ8e88AfGHsJfp68EixTLSPb/YAATuMJaFXLPM5O+MngBxyewa+NnJL+g5qS8xvrJyrgyfKXlr0yUHVnNz8sgGwvWFfechlIX4kmfbhKkqtLn7MXTXKlbxtJn4DSlwvJdYr5dZC+vG+S9OWi9OVtQ+n7RzDzQamsgf7j19qrWgyVvgCi+O3mYyprEsCUXs4vdZ/AxTO5CeY4FAKglYC+1EohuTBa5rwbJGYmWFNE6lnA5lky2BDwBhQgjvfzjzxkM8RKQWpexM+g0EKdwP6OZzUG907Jx2oELADTlxC53QacAJp4Jd9basMDSuv45F3u7wnSdHYSv1rQfjXyLQ98iQ6Nn+9dYsN35uXxGFwX5CZvRGDBF903jNV57mvr5GFugI+uBIaPeUDs7lJpB+QDDUgUH1pkdwJO9cR05RO8X5/2BS4/WaI4OgyUkD7+Lxgj4CyDfEAPfRbxx/GOfnYCk+h7oxzMU49smG0IfgDJb9H8VEDkQ6dPWlATQLd8j/IpWh76pNRbwhtlawOqfeXAZfr+0SUW9zLDpmvRL68JaLvToNofL9CHmrW5TMCKVC0Nx6DDmRDvJknByPlV5LOtQmaw+egzAXuU+wAeOrnoFllQUgB4UNugaHe/UyN9g81xV1nE2AU8EQ05jiqtXgHUa6gfrwlCeB10nHkt7iwxtmestA+PG+9RMqaUZt9adJ+lvRr33cG04FQ+nKXFbBetsWxygz6BGYGqAwX3BGcjEKX7/GQQiIfymymJAHVTIA1V/Lf36RygezkfzHAT6FuFqB9GkIAj6CoEfe8UKD4EXTklMTD2fY+RsRGwQ7Ys6NkT7AnkPsHnpwmS7VZWoE6q4P3KgYNkKRV04RfNPALFfnD95xLxHhqyY7RQsOjYE+iR1R5jS4REWdGxDfi26hgYPzHfMbm6SMGCJULM+xewsQW5HBM+Y/nuE+loWoOm5CqsUllay+WMa7nrJ+q4q9M6bg7FYy6h6MBT1mPc7gc/k36OrQmxB09Qh8GkGF898H2hd/zwMK1BWaHz+lJNwiNon8cbjzb1jK0PjBTxBsOk9QVh5Bp+fP1gxHtaVSfkj0SmvPdNeNfMSYzaaBYlsn6tNJ8t1v2FRRsuYVi6/TxYCWb3EsumPGYesyB9lXRjxdhSnPIzdBOgC6Euqx5UaGqMLbFODjDA+O6/VPxTO0cV0JYyLGOx/aAzYf4xBZVswY/yMbaE8XwM0qG5j6XoIjwzMgafRXwxB9mCNxNXZI0xRf55KKPxRHn++Vg7j/qm/oRKq5vL+d6S2cb0LDk2PeqzJTL8V4dzsT/nvsyvaPWfpG8L/Te7GLi2CkIAgENL1X0NfFPluXjSc2gDHDgBAgTNNPcaZ1nrtdLOXzGZprRNA61t+pXAgNa767xd53STBHWmgZqm9vRtKm7I9E7R7e7ev5ubuOkQrooNhYaqyNdVYaCCunmwsKFTKJ/5P8/znqTpF+r2/+T3o0nOeb/f533e5/vBGysaUhHBXfsprM/KY+gyYH8nUNMsqa/uTYoqpfyT9j5UyvunosS2hu1Qv/WEoGMnqBG2KyVvdcCNqOSRggRFA2nCSVHHyo1sWqIGTXVns2Lko+BqXzqsSFISZ0NJXPYcJI5bD2fq/qb5/PNfR87n7J6LzCdjzPncdv7z54O+j19iQs+8mzahLzGfBz8ZPh+jmnOx+fzo8bHm8+i5LzKfjC8zn8PvpM2Hzvf54ecbw4Cn/zYkhn57oz845ouGTDC/n50htZikTx6jLDxTyLJWv0XzbBylHSN9mwm4+pQIV8RxGapxXG4YF84nL11ACPw0ijLltT2afK2IC+cT3zLx8RAmtyA+9qNlljS/0gC45Tr7XZbAp/DsWlZpIIRKqld46r8cyZhZyjQ4wZWiFygy9edvQsdlVlKCl1mZz6L4bGwr4AClytY4Ygbp/ZnQP6APh6Nn1yU8FuzzL40NI/WtVxweW99gjGf2DGmrf/3PQ9rqDxBpGVBzylwWVmgfTPoy+k2syjB0P7Ab7SFL4BirtDC9MhE+lIWi3WWJu6xcq4bjK/SoW99AnYgFjWtPs/jnl//RyPIui0dteYOLIV6H3dZxZMm1R80i6bCl0XdN6n7JPRoZpr82Hv22OPx3ZMTv/0j+hvWrOzwOfkdHT3uvpq1GF8+XaY1mxV3GTwnJ5ybV1nBzS7VAKqxHseDFFh4KWriVgBkg/PHnBbLtAJQO5LvSYBupSBZ1Fxmf5cuNL6VSVzI0lXrPkEqdBqmp1EcM8szGzxnkMIdIVJ81Demzc5P67PX7xtZn84mhFx/yVIfTcl4VGZCt2gIgcGPOCfsnDSuqm41N5kuIqTIgjSJzKCFoQds+nXrHU8BYieQOYoU3Hrrmf7VxiLeyIm9lI97q+j9k6oStKBOosJWkcQ0j8AkZV3/MGiysXIT1AIwClHctLEt48bFEs57tYqqKIemV7wK/JCpfA1hWXDZgzKrFRsVra1i+dJT+vmP0edV6QUutBkt+P3SUtG1Evx3sGkkz6nfyUL893BnMhH2Xikq21vduALVG+AJ9D0PVyf5fPHwxegYxAywSUXn+ywCUHN/KTyNkTNrZFMlK43XVIWgQb/pWCuJ13xqC+E8Jy6CO20VVR1In442HaysxMNUOwlXQI9mLpI0GtVFpI/ldxsVGQiqwodFgdOK+sfS/rMgY11MLHmhhEm+hiA6G51OlziAd/WGGLl0eWzSI5MtwTTFdNwfe4kLBajFakWFk+sTN4kXL/3JUecNFy98zqryE99/wi28ulqx6a+hCvsj9mP0Wvx+t6fdjNSsypQ8grfwgXmvGagxSYk5VIfxqOfp1XRq9v3/EfT844rc5/f4H/HH3hRT+sCTxR8OusfGHxhzjfYn76p+M93Mm3M8nAp/Z7zL4v+ZT7/mJoMOvlyNfN1UxAMntgot5gahO3IUXs8QvZomu4rT2/LNJWIUqF32tL+ER8dY3BP6yNP3Ork6vMJ0Bv2TwqVnQIy98Al8ZNNYqWiWq51YKwGYMrTAZsyF9H890A6ipXb8VdEpK9IWotnck/X5wzPuernTeCDCJyUudTjGwmwaveuc6GBRc6DgoV2pQ4T4R74Rvw7Dg47Kvv8M5vr/sHMnxjX39cnyf0PYLN+r3O4dt1DD8Pvh34vcH/mMM/P7KM2Pi92/+9xfC7/XsKAZd1NtjXv90pE/qgMTzIAjp7LHAx/ZSQ6CwFiM2syoxGhA5/vfBUoVrCA+/zvar5oSGhxtFVivWK5eoLljrxqUNy0exX7h/lx4Zk16rdBc1Y1YI9dvbk1S8SBaiRtpEmTyw0fxjITSO5qNsFmfWiUxSXCUY4dhVQqpPp7FhNOq/WP+kR8Y8gWr5rwRdpEfuQk/58KAQuhIzukXIir+yxKe+hjNrGM0q7FIzHseQ/v7S2uYm9efbMsmLXkSqhCwRyAIJDsgu9aP1gs7jZa+q1Q8Pn4eFz6MO5rGUueqgO49PPfSQMIr6S7EdyQ2/CtHRd/YilmNFztFIN10/PPK94XPeSyPe67kcBdlzRd/LjLWd35zZdjBwCbDxJH0ISHgB8+/+T5VpS3uTspfAZQhf0+zGADofJAUyf+bvMhQ96bI/V/9W/8pF9W8p+XThkb9ZPp3985Hy6Vt/M6Z8+uQ=
*/