/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INCLUDE_NVIEW)
#define FUSION_INCLUDE_NVIEW

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/nview.hpp>

#endif

/* nview.hpp
Cw/SDfsA45+NBjvE3RBO9g6sxa38jmjMaelIkTcrk/tG+qGCQUlj6sLLVvKaosYk+6IGTNKHNKxUMPi/6oHTCCRPAIBDS619fWAUxdn4fWdJLuwBCQQMECEoGrDRgBKPQBAuhGrgYuRChAS0GNMrtQi7oG0+uznNZr2Kb7GVqi0W7Ytvv2wVBCx4l8OEAGr4EBMBDZraORc1SEwOiNnf88zsXRK079s/foTbnZmdeeb7mWdmno/BEnR8AZmeSfmos/fggp9aswJDdRYXFuJNKUPLwni6s+p8HvsFubJkQOz9qI14FHLHkZ/8lrKg0jty6EMdutcwiNFfZtxJCNsD5LmGckr3LENr8h5zn4f8kLKUO8oGE3Jk7cCQQcSC3hoYPq6KoP1Sof2UdqL0a1pWq7NDnEK+mRTdSXpnxAYPa3m82WgNZRdwmzqyC+zVVig0XjlKgRG4xx5BmjDpFDVUPKcgRZikLE8C5FRg538XyGqVbp+JJ6sR8xElSG7FiVSVJM2fqVwUbc3mmf6NRlQ0XZ3cuBSooO6GkUot7QpDoyGvwZYVmONK4bcGzC67uRuaVROt0hFNtWZ8aC7lKnIBHcOG8HhZlOlE8C81ZbscgrnZ5lIW27Frv6cstuQ/autrb84zzpQiaysTtnnXwkbJkGdSmqRIPPrjqd+sNBnyLL3WFJgextVCUm12psh7zf4FyHllvEiZi4e1CezE/kU1x1Byg3TdGN1MSednDFXgyaGsRhJKanjHrizyF3QV+gtOFjKWo0qKPpJ8yNdRPZEKb3xxI+o2UX+suPCYO4wyX5aEgJoELVl1EpsyI5jV6uvlfwcOBORfaix0Q1fQjwH9k7nFfKiQ7HlO51sRrM1xBnUCdrrrpNfghvVcacHTdfIZPVBPiTGKb9seYxTHoTNc9m/SVaK/6Z5iOo7OtLjO4/KbhZpmMqmN88uonjSpyixXJaHMU584lfw2NTq8Em7E4UVoU3ax4RW+xkz5nDe1K64kKZDQbDOgbPAIUpFKR9Yh3HHG4RXNYgusTuGkfbiCF009nHXaeZj3/ZcuY9vINHlEG80sBQawGkn+MpMbNtjpmi6BIYzH/CETpvERBbsBRYafRhWKzpmipdk2M0+qSoEYmdCoA4fSOy2PNOQZvQ8AxvKQHxzRjyDql6NaKIgH3TLQWnuusza4voFrzjUbwqijkZ6bZ7UmHBIoQKU0BcoYBdd3+prTAB6gKsss0ied7HAZOjJ0fdbxhKCY3pxnyoRPSlzdOTxRhU0thFrl5edVB7T3gBmVl0Ccm+GD0pwnu+zZy5NES4ND5fH+K4pTRzRwQ4DIBZHNnLOJfwxP6eTlPShdbQDYVUmG6ruUYsvU5REljn+zoH+qq4edDJPeS5pWLgUy+dcDUiR7k8kcwgXlx/2WBpvi6uH/dMgSDFvytIKkcjwgRNVVBZGqv1BPZeF3g9xBQUa4TTf787RGrvZSOWqbzQOEYMjMV79AZVlJGJwtxtWGbm9IUUcMBBs41TyQq9GSItHrzfSQK8/TWWnGxQxmu0E0Kd3YG3+bFW3l9VDIOCgEybyE9lem4aCZeiLDdb6o5Jpjj/A1FmdowwhADRnQr2oixRHNpr72MSf6PlAGoHecJyrT96KOGYgZ3DC+qPBuN3ngWYPBktlgy5OXdytB5QQM7gTf8cpJNVbALxvGeQ3etRBrvh4LIuUNiTUZY8VvSIFY8RBr/LBYcmk3eqAYw6dHVoAe1Q1ib5h2SUpE2WxROgCLLyXNvbC+noY5dvv46Bz77+u+hcLDe5k4qGHT+7UoqZ/sFO2iA0bcfMQc5ubyFktKpmEYblaQ/7wm1eMvM5Kz+XTZKSI9n2satA2qQ7uomhAxAwIvpHH2RuO0fU5JlkFsDh1RY0FkpD16Xd9HmL9oza6yVwKGsANqVEJkAnRRsTeziKQ/913IdujF8HD86mG4tcwzHLembRvErVNSqFbu/5pGD1PXFSmlDmgvB4ln4T9l4UVAWjvbhUSGapUQRbYKark6WagUtJvfGYJozS1usuLXw/ArYMoUil89aGJ9KRO5jzEVzn82hlm/VQFAkcXesauLh1dg9TOsAr3iGHLfOKra+Vg6Kt8KP80UAfpahU+hKu1ZgTv1UvnnZkqXEPe1qqaMQ1AYQPVJhcXkL78aLKnNoBYrrvZ8Zzv/XFCK9FfOdLqSqqYDiRTfGLe4PiBealg8oC8VRhxo72AL1rCbV7yXZV/oItLM1geygyqhSIlV9u7fxCqL+DzygLBairiEe6VIuTheE9PoyhJdVq4f0CXDpch9wiQpskBgUVKHxWqCWGrmd3z4CYwbddx3fYgMXa5wHUi9ekVjQumplLwqztK019GqjZZcidIuj6MbDx606Rs+XY0klqfCYDAbKlA5T1avhyx6Jsab6sF/5Bxsi8qi8prTAWvsSNvFOeTEVHwmp+BzYhI+ZzvwmWOHZ/kTyXPoK3EGfU3k6Mtqoa9pBvqa2f8a53juSWsm+BSXYUc6fVt2TN+Ft9ncjlno93UCKddiXQ9RjVDCF/DjjvTX0PBOCjxHWAyBFmsq/apLksq+dkjyQhd1nkED4MnPoIRTBUTyGkkIhncJNFvyVgisyAdqS0vegoJlORjBIHIQ53cYpwJha8kcyqFpyU+gVAHsob8MFBYpQamTB8qsBoitj2uCJE64zf9iOp6RlPM1sLeuWeDARxo+MvGRiw83PtbgY71fxjPlfLHNd1y4TWkKEovAq2b/Eprev8SRL/ZKH/NCKuxNTgc/MwmcPN6/xPJ9MSJ1mgVbw/gF+eLllStCSnvfaSnkyDiRFbhbOSF9jN+MC74vXg6qmAYgWe4UI/eGl6PaoHgt+TlsBjzFzgqEWowroOrh+9+OiqSgQAkGkWVvD0p5aM1XC5Qw+ysov7PY7+Zqb0eNmmg8B1YSIQkZH+4mn92js0lQ1bm9NpNg7Y3jhK+AhFEMO43oMwpdO2mwSTgNG42YQDBu39BS+d0LF3YKk3MKlsErJQePocQbyTHUv759C7ZzuM8B9FgAA/bQgOoE8nfwaQ1b6BkC1Z8/B48f/GnI/e9QSrm6Ggu2eo2NP7ARll1lIyeLXaQSU9VuiQptiUnC/dKAVm11brZUWskZB6JQvGGcFZTFTp1zX6oMWmChkTdyFWa8voHvmhC0EOMoBgVp0vMkQ6MaA5Dzol8vgiJ2Qp7qtuhxwXhU2wFZWslGyAjgkalpTIkh8hafsw+t3gl7tHohxcCO5sQ50iMOs3iLkp9UdynN+svxgqPu0rX45uouTYG3OE56JBUNzPzKjuKKC+QGFORQgijg7eUq1mADrZtMt9eAdW+sy6ZQpygLUCnBNdR0DXQqFN+tPZxC5v9Kiyld/NlkVL8DGxk8q8FKkgf46E5BKbArRrwANDdLj1oMlQ6l0KIsgSa8RbGPNB82B6O9DcvOebszIsYTARKTqfBocGlAbGXHVS8rkl0RDzU/lKrk2pUU/3qLmoYHiA+nKjY3DEEzbkIf/Caquiz+TqnZ4jtdcwaVhGlGDQ3f9EiuiMMZV7mnbGWjC5nfLXveOW9zkJZfojnRBGxe1L2M1ri+Gsn6jpxCR0G/RraCg5Qm0NZB7WdyAzVBXQJk8lHvjIp2bLzvwQ5R6cCVXuTk0i7pgaMGZXG/7DqjbYJF86Cb7Pk1FXhztZMxCKm2gZlqIlbqe4L62khfPBoTwm/kfDxdBOWGJ/QhSSUMHbCkMkRfBJi+mNieieoroePtJ4rrPPkUmoL2xMvxOE+wpw2wzEPh6qpjI38ZjnwYzmUO5AdCfUp59o0pPwokKfekWJyHqxc470rhapx4xnRXG1fo8RqKyd/66SKJB7t0KIucPgpaUBEblDkpav9hIp56uTrV/2YtorjOyIuh3O3Egs1AHLRuJ+UGWlMT9bWxmtbNo0PvDqkaBvRcJS8ph47nkTl0OMfl0NGcLlUdNYiTKBdYCrQweexXTOkJShB4yI1UyhgPHg3rUP8H7LGyjiPbF+CdfKgcX78CZuucQo6vX4b3s/mc87Bo78Mq1PL1czEIT659gUcsfuFmu7y8P+v0wqKdnLAAcJ62OYU0P6Wzy9Wjmh7YpO+KBZzDJlicIiNXHmJBN7nQT3veFj6Cn6rwZEpbn1I/Wcgn1bFk/8Pg/DgWsA3vEDbrkT1k9SdMWVNNkoX3IYMWcp0LlVILV6w+l12cIs4hN+tphfsAUHrUcw8AwVgMEFlLC+P2kJEMoJpNLm3Ro94A6c5HPalYzw+3sHtnvjfO4jWsgBmOQq6qlbydEDtPR+nRkagrAkfcDxOomp3ya5AlnatIw+ZPuoZuWlnzClal1K7GQ5PjBcaqUXY2kJI8qGxNwWPePEZY5guT88VZXqM/j3NjUf54hRYcOruIvPkUkEQp0S9PDfny0lODmOncBIqZWMHa4mPHF7CDQkVEKUWUod3DTqCkKlRowYlmj2oGWov8AABptzFiykP2XEK7rpYKAz2UTM2FcDkPDZgpdzKNQ19fQSjToaniPG7y+RZNG5TgQQRYN89Mx9Z5FOwlo+IQ4dRShLOYmMHnpz6SbzUYsuOELMXGVrwb2fo3VRPTo1RlUlSysPopStshpwCll6tSpBo77DrIzTidkIrtcSNTA5QvrZg0/5eG4vKAKpwFPRsfpGb6IkX+R3qct1Uudq6P1NyhcMFzFnO+RSnsAWLEVvtTziDO9Jd095pzxWlQAAVJyrRhpyYc+R96KJqKu5iDqagaDLIIJKGi3IKeDS8M3dbNgsUAiPkUZaHFU4xMoTlRTLQEMdESDvbVQNtXWpyHYLn98QjKw/km4oLsebwPNaMiRngDkQHvuwGnaF6SMySMZnghgeIF3ofEn1SdauB9NhRz32nFhkYkY+DrP0GzLL9CVesUwcpolc4aRb5eoweQK/ncr/NpWslnHPTFPPE6iojSWG7DsVAC5gQxAxCT5Fhjiwhfj0y0JAOB0xCSZqWH2Vm98ivUHwfjqQS2IquyTmdPrp6Ihz53mS0Ve4AiJ3sOokEXMTEPCDronE9IMofFw9a+O4IjnZnCPNri4tYgldbThHyf6xjfZ4vrKCXd9h+kh9Wx9nvJyNqP9z3775ru58bYIOIfw3s+pk6w201tMMIQkrbgEOqmQ6iTl3C37X/EIVd1KQUR/+JuWNqyOf5JPKJyLuvhn6zDQcmOtGAdJL5A9QYlD1dw/woLXiyeh5Cp2qZUBXUu9sBKSV78OrqET9AKzkshS7brfM1ZrYBIrh4HauOuOaDehCOxqh0KpJT2aOIZusJHRyRuNMm4flp1paqLDsluvFloSYJiOl2d/M/d9IQ2pbYq1SDEQ6eTgV5sU2Qu5n1/oUVGXr7JtG34nz+HITWpqKbtKcqdVNBHe47hYJIPs5osxAfOb33hzsI7s6r0wcXbI1phxiJeSScJfixdilfz0CLbSSmttAMagjzYh5xPKdLP7IZN12EJeZ+G6i70yR8pGjL7f0cRThppNg2lXW61MSuYoaFi3b8Molg3Douh9HuRp5jINDGjD6goGx0vB7D+b9ARnqaMcr4vTKi7jKctwmjFMfWU88SG+N7cNCPv+yXyxC2wlAtT0R4hU1ogQanFKq/m1mtXww7wVa/0iB0vhgBA3WVs2g0rkCAV7s7OFm+RHnWYN8zILknadL1SmMqECibyu8V0D9v1umP1LtSOQ6XVydHdcPqQT+SXrEnoLmIlveyhG92QlrwdXkyfgDb7DN0Bv6ibGxKv0WbnxtRCKN2xCAb0NpeFXkDVEXhzONatzc4fokBCSqRKJV44o38fCVvDnbh7TKQAwjdPhVnLVTyCK+BooIsq1tMN5isIF+imvFUNv4lzSOWcIUtbLFcnydXrmx/DC66FzY+hPZiFLXkVj/w37FMTybj0KPfdpgot+U8AILrCzUPEZSe9U5mqNryAyVuHUlMv4O0huLVN64ijBr4O1Z1JDo2hGjMXo+GORPLRFCY2Rk5NYTeUnmImdMXUZigRchCTttHmWhpVsvHYOMqpWeLrFW7/dwo2UtBWVoTezTANG6hfQ7apIzxkFCxeJVm9kNNrEL4aWxo1XNXg7MR8OK+DrOdQ9Ay+QDNux2Y8Mlpn7OfrIzhk89JxvXWTg1vQ7EDeDObbzXyzmG8n881lvt8wXy7zPcF8i5ivmvnymW89863KwW7CgNUYAM0lT4mqUa+uQL2RUIU9TFaNr9Owx4S4YnILRo62eTHrJfcU1g9U4rt6HaSdWkxMqADKmUMve5PqNA7fdmm+AZWO1FQP6bhJFPt88CRSzxy0Aw5n2n1p19JeA7edJF07yHmp60m5AAUs+tMTD0TF6/VxrczGga+dgjqOiXYaHa6nUB8IV4amAL/dlVRxByobiY71EXjHQqcIUjnFQ4c2Wg8cQZr7qcmBkEeZ/Q88XPkTRCjWTlVsx/eOuQj7VMVW6sllnieoh+Z6SsrBGAZlNuawAyedMFbKwYgGIVHKWUQdqGck/QWsDgXxAs69Fism5E5aHTKtwA42YXH679DLztcHkbCmk96NDcEUQxNq6Gs2JldmV9I2YnH0wrIG0QvLEIFeWJoHuTSJWuT+gZKDTVbR+p7VwaBp72ttO6I4ZFF09uQnxWZP5vDZ8z6dOdfgzDlw5eqZg+Z248gPr2Djlq3GeXEI58WruGfej8te7iOo9oziijY1Tqd9o0OoayFEO8qjPOYWGrmSqeAIv4anQlwFQVgP8tgOd70+REvHv4NXBY+jFefarfqJ4g5MFRrGrySdtxQVxqxCwxZkORoFLnAoP+4nL/uQ5VtrW12mnC2FsOWKWncJCWzRuhdXpELyOMQoLVnZ2mQ3FCvN9KSN92H3KcekczXBz+KEB1Sb/1l23PYTG/yWOuDhSYNHGR63xcFvGZ7AFeMJ3GoI+kl5LjwecsNj0xp4VK+HDw/iqdxP8FRuM57K1az370ba1P8mPr8v7vC1CkuUY8HP0BL3uKH51cT5Nzn8NY7vi19K53ghXQmiZe1EZaw8zr/J4q+xLBEvIkeKWRiBTIt5i5eIfSvKVpeG9uF2OaMt43Ch0hSNMLZhHI0QJMNA5IsXS8IJUX0x0IRZrU7L250wYoQxC6RLMzdc8Od/Ll0atXmkN3EFTEfL213wrTRkXYS9OrLEeeiawNSgFOBKQyTtMtUIZNuT/3voKQgLkcRo0F0syB5V5/AxZlnAFcoc1aZTonSTf6Bp+UzUVGKoQOW1uMIGqB1D6JingzvQiKgSDEWtiR7EcTuNGiJlQCsOxfAEGvKq2ANewCP/YH4ryv22lcZkgMkhzJYKAx+CGEe9HEmcyBRckYxUfakiYyO4YnjITyyIH+MS8LlsAT4fxfFFHpLw6WHXwGWDKsKyAioe3DqUkdC7Ju2Y1GxxivYN52NmvXNe9McBmhlfgW/ieJxthONpeTCohOwkQHhXXoDpvhYe5AVN5wO/x1NcsW48hNzwmMGwZxV8O7AGHiVKxNm8kVfi2KyTWizOgQ0XpJw2ZCZeXSZcU4Eu8ofHWE52r4FKDCS30WNaaPS0Cu7HEOGtBCQsiDFVX4dgVmZb619HjVMoubADFWs1uhy/r4Q3Xl3xvu0U4x06jriNYvRTSrtc2uY7LVRosw8eRyymROSqk2jgo6pd+tICbueVDXeSvUAbw3b0c/DMg80wJCN/gCA5TjvB4GFQFER26Rm0zdEujKSGQmA9aadQldI29Y8trq5aaIO6qq4t8No4ijIX6g3h6rKon7a4OrfSCJ3P6BE6ByN00ggM66RRKtNhEG9oobXG5RSaY/wEaoWBI/upTCH0HAehZgwNkffjo8oXvPpO6q8Duk5QZoSL/I75devdYZ336BbUqcvM5iJRfFQ/q4Rp4bS/teYZIAzic6XI2A1fUO4Yy1trISim0BIX+qsUWhZ7CCpkViJZp0vk/RbI03mFr1+HlgTM5GmqgDJi5OvjWEB9A9OlAUveyVehonz9F3g+NtBPt5i3QqSK57bFOSqSYOl6swGaoph88bh+ZcP7UNk91T95YB988hSV72jai7OyDQbAG1dMVP3B5Ip12yiPye5oOmRHZfwePRzVVQsfcqFUczfd6CEiePwWF65TyqGMd7zmY5cq1gKAjI4iN1EeY7d5AXF/xSoIPIDFgj3GgC/KvvKStgurDGGfxcKeqnCkGQ0VDkhQTB6sZ6xeZVQ/R/hRRGA9WvJRSpk7Lwp50oAmLMgKNNoXNzxhRYMG5dmpiwUuNwetoG0gRX6fhak4xG/uhtIrhMtA9Ut6gIcZEYwxgzxRTfWgmMmEx1nTC8ngSWRTXZysN7s4tgJbnEwDEGwsXENJ2tg9xY5X9nPRbtdmoye2dPIUp1FtzMO5qOi1ri/wSAmz7LOxkFk76KbG7pgRHz74qU2aO1ITZ+sFQaXl4iSJGARHvsDli2OKvD0qV+T9WjUXeXu15JNYtzg5FciElepYMhIwu27AZyw4maHCwfuVAq4o67Sn2HmkcqUzkZahCJaviFW5cJXBPWYs6FZpbqYmZEbbZGLGEcGxROCW/JtSSHYb0ChqMmm4FCvFFnDKKbQQKwebAe0fpRDhEi0hKYlFpzoehtk+cutxZg+CfAH2u+p737YU0buIgzK/rVg4qlZrOuJNP9oIruKUFqxkHxMIM8+i9dS5kLNOZ5dx4mxvPHlxrK6pBvzjK7YDTeTPs8NS1c4ofbNc2qXlRQ+/SSZVGNMlTKSwmdnhmAmFOZgulao76iJLbbjzOg3FgEzKk4dyhH6nQQlMm0bJbG9KRT7WosU6aB/ijDeBzElmo5VDtlk0Lwphnyaz/SAicy2X96NIkjJrP4LFvdNeevjVqVhoiBUZg53dvIRqCHvzLEZxpVQNW4Y5UMLnEVDW6YXQEjTsmm83hRWQvWqGxqBXJtMpcj5jEMf5y+xFrN4IU7imiFVEas5VJaWqXRE7Af7aJGwBmuDTZogmjdQyWDmDAzZozE6ruVsWUXuhJj66ODwDEUKuN42MGEHVlKD0t3Cf305TyEaJDpQ0ZVRdE61T08ZxzbkWg8RpzbnWeGkNZ5Dw+LpTPRv8lxWPrehIeHeYyYtmHDjFVDAdW9Uy1LxYlKVXtuDhdgL5w5ghcm53efyu16BZOtGaCJSxzEN+wFGN6K3OIOsdHpCufwsWbQctMDWCCaW8VQo=
*/