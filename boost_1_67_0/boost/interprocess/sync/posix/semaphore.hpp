//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/posix/semaphore_wrapper.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_semaphore
{
   posix_semaphore();
   posix_semaphore(const posix_semaphore&);
   posix_semaphore &operator= (const posix_semaphore &);

   public:
   posix_semaphore(unsigned int initialCount)
   {  semaphore_init(&m_sem, initialCount);  }

   ~posix_semaphore()
   {  semaphore_destroy(&m_sem);  }

   void post()
   {  semaphore_post(&m_sem); }

   void wait()
   {  semaphore_wait(&m_sem); }

   bool try_wait()
   {  return semaphore_try_wait(&m_sem); }

   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return semaphore_timed_wait(&m_sem, abs_time); }

   private:
   sem_t       m_sem;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_HPP

/* semaphore.hpp
6iOXU3mT0lXsLprPwumQRdrLBS8RmNRtMkp3eTKSUvpFCS2lT4p8jaZiQ1JwpY1wfv8a5DXeOfZsqxfbaIrL9lmv8e/EX5h5CFe8mEhsbt9ziv54nPRs42MU/yMSXv2G4be6jHr2it7kyvCnyjbo+cuqHJ1YxQ5IiggNXlXPx8cKR+UfXj7aHqp8uL8any9+v7iXXb14/Wya36ixvf0WwqIw8ZfnppWSNHz5EcZoSKBbDfRjbQ5b6JxVhc59FQmctcO5il08+mf2wfY++vz01fdrhvzczytXD36zugQGxaN/hq952M0KGXodH3vjVjiDGX4cjj8o3HgRRgEnIsvHjG27T9KPOa4erwNbj/2/QsL8WL5irH9p6PXqz/kEGbNmFB1en5MrvEICFKyx0YL/KiGYiZ9gH7adq9q9zcy3KrGXGTr3y5+byOLawXZCfsPv1xdJaLRNnBzmori7r5nBYjPnSb/s0pzzMbrd/MyRjX6VGnSqAbFifqRSOjp/EKQSdnkNzraZL6ssuNUUNcpsNionSYir06+6Aa+K3iBz5qED/dKBFPdc6Erz4X70NvPRxRaZfnk9FHjEnkcFdTplEPmShxsQRvXDhDi0p4+gQmNNT46WHU3HpCZCGpiedXKDbrlY77Oy8BAZHa8b0C6RkxSabIch6NK2W0gL32tlGrxX26sTFd5Xs0J06cG00SPJYZnBkpQIKb3NeGDBcMoeV3ji6Paz07TrvPSP/AAfDZHCPkuMz4pf+CJt71o7+BaOGKj7zHNDsWS7zW13+BfInjMYgrUdnfCRKGsQv1NSYKkU/LOsBHlZczPRyjQkaCm6oxlALFwkLNPPlj5lQ17YFPsjGZH/g8I2IYLDW5bBmviqJvoQdfids+pAb8tL3JKtJ9MGh4scQgb4TIeSge7WXTNTERlWSP03s2Fm+MtVt7O3dziCuIyiaEA7OyAbokgMca8vrg+LtHG7mE/478cFyO7IKzpEsHxio29lzj066BPDecauAFkjpd/4EXqeFBHQlbeUFxmp0HNQSmJcZ8AIZ2e0YAEuVYtr2nf0wfs9uKn+O/l4dWuqwOqpCoX5wqDVjBvPQZYQVng6XuwAUjP6a7BKohvkXQfU4Db8Tg8HBAvxGdRCAaq1aHJW4mjMi/N3XuWbx4Z5bmuU8QFTR9eRAWZFR5xlpvxW9h8kh9rHiOxlUy3iudydMr3HmnVhoxJ3g9PM5y81rZZqmFQ/QUrP54SQMjmA6Xm1+rI1Z6GOFbEG4b0F0xNSb/0osY0Q8woFPEtrj9Y2qVf4Jw39HOS2nfsew5piITEJ9ExA02g5mha1H+KLorcngCjRyUscFxXEmcD396k/d3JHV1QuvypmoipNKACKJBH3G4wn9OPYf3XF+tirPmLAH+UYO6nZd74zt0GtZC9zXywj1Ar3xsxIe2qF+NC/CQ64imabO+za4gyE3wIB6yDQgINAAMBBwEHBwP5A/ZcgHQAoZmJFQWiDojtzrKBkGfdCk2TV5ueW99AAC/8QAn8gYEXGdy008jyXh8e/3rFPHNBl+mlsQcM1TXJ1oAxkCeeti2+Cg8YJ9y34O4SHTmMP1wXfGThASGlZrgAqt1gUBhs8RhdPklBeBtTdWQyVhW2jxWp5JOfQteVArpB87N8RqJdgKtKj/A/LKN2OHGx+vir6pfs++r77yFqL6JCwvve6UtOz4gR4+Dp1ZGxW49xghuh3SwYAF5zgcsTG8FPmEkiIVJU095HUnXVgu0wwdPBTclP4TuQ7h1QUzsLMRZ6cJ0OZN7dCyILgkIYrvE67YRkv4/Tl4hBjvopIAGWChWjo6R6RMJrGxhDG1sp1B8OIbpA3S/crA5tpctWEDvwsxBIIQiQN5SOSAovUxhFC9n3pkeGLpwRiHBus0cRVTZmajlGlr76oJmB+FrXNfG7wm8DR5B339AMBrCWv1Cv0qDk5vWcKeYfKzb3OjGXsmsf5YpQA+o9CuM+Lk113OPMY07d0hhfJMky3b3WrVuDMQhSdVQP3xfYJwDOJLVtnwwa2yTYNrg9IrNc0XmjRz4DGGTbqYjYbIfbbQq2+W9uOQrJjE9Mu769htifXp7GyCd5HdVWFiTgoi1SpOi+hIcmKz3+qWGnpdUiREJ8CapUnvvth6EKihEA6vRJYS0pAXB1ncuWExQ3AmMK+sH3ib49zjnbcyOCO0+VTHfoFOjr3EYn2hgTMZHQLo/lRDW2SEJk01DJeIoVFfGR4Gin4dPC8fPLmBuVHw92Op3R8EcCGC/Ey099OJqoKTnAR1pzrgny9pvc85iy5C7zOcukbp+O5+Ol3pc+G4Jgriy0YkmE6M087kMjqI+zE3WjOTFdsT7xlZ4Ppk/gL9JBSoMblpj/FTsnXkCT8SptHeAiQVVC4wH2sU/RtyogSi5mjy1vV5sLQfdDfquvBfdFDfpNDavE+ieUYFPWjz6fSgTc7WeWP8BszwkiDX2MKknXUkPODZMNyjlhz2tAxa1BADTQVoUmRtTtsn3iE0SjM8CUWkv1uoK6H71lgulSx6q1ZaciJTIXJbHCnGzek5mZ2gKmZZGJeGTlRwHAVhFLGb0xlsMDYd5+7z2a+AAQs+9PFP7wn7UMhnmBhoVoyApyR0it06Wx+IOS59pmOCQDxgxosiwQraQ0tN1mDYbMsSqjNC8DT5SxolObR9VZxshxTsJf249q6iC9NmYjMibrVNa4Pwn2MGgEHPeKIPxpSAseG0ZDPLy+mx3YRbQ6TIYfpOdOrtxpQT3LWLUGxFjuAcxYsFJbKazGJ5kMo2FO3MO2EGiSTwHMXL+ol4csppnrgxPaGSDj14a0TiTgZOnLuNUKmkSoh6ur4xUJqL1SnaFVrHT84C424F3pOsI0HTtkf02fnkq5iXiX0jW3ZYiBhaolC9011Nr4nGcpW8LI97zwyTtswfAhQHRQLrZCvCmCdYG3JBr/F8tVd7Jkrw0OGnByWapEsUQdBklu2R9QGS+pFpM60i8Th99tVnw385rcqGiehiF9igNAJxDSG6qZ10XDgORl6yzmk3KnJBIDVsOsi8xsV04PAAHYCaqYsggIMHfw9fY+JRndSX16HGvtNzHpxNF2y3pzboF0Fyzcv2E9qM1hKlMOHGtXSKwb0qEB2sJZzdgHmflWjBHWUYx80UNw7CypUtvussmg0VvcV2rOItKFppS2M5ObtY6fLk0OLnVqaTHIWPyc3PK4ZC7izFNpbw7dkTQHq0AVprEsIqmQIOkyfSEw8gUm1JhCYpln08QAqn4UqYiDJUI0KbmGw3EWeak537GrJQjMiCpfyysdsCEQOky1kCqopPp/UgWNY9WO8IJR9GsYwzJx+JXIkGo/eKOGoEdiM2R1xnPxl+SeMIL8BihrFtwNCcE3zlvivueQcLnvD5rbrZ1LFhABA9ObA8yhHIbyXoFwUDMDgclAR2VBdIU1O8fJA9OvszY+LNPFZOWKfB30H21sLivpWJ+SUzLUrmyYZk5MhgnAhU6ho0wheTcbGdpTlweYdaGdjyKY/ratnBMxpDIN/4Yb3aTSGuMrmw7BAtHzRs31pcaEJlAtfKjoS83wbw7SlVYfFb1+ikxAIGRBB7HcrO+JaIsmhOWxZqJFzeCt+4ppCJkYWBoyk9x8+xLbFsPuAz2aAKxicyMuCcnvXAUrkopgYqaEoFtg3I7gZ0a5Hgt9W9LwoC6hm5Fgqe5HycfS4/vXFveIBmtpml7JJfS8gDWM626367fgBBO6k26tOsVOGOZFBIFD+m/3qHoBNp/uGG1aLFfwngLIp6WSVlaeWpJWd8MC2mT2E0dkUxg6zle6C977KZH6Fir6wAQbhKpxYhRFu/QVO+F89o3VtFDrXyV7mykCJN7H/IFm3AmGogEus+GU8vYweFXb6t52ByNNVatCwwlqk4SuitbwPCXDeQYyftiJUZcsUMOL8hBRRu2p1sEgp7maRCFC5X45Qo/YmhchX2AAt93RTAxNgSK1/9am5EmAnF6LP1KYK/GsOmHUh6b95YqNiuln+9HGMjReqIt0pwlrGTnV5A32TjaC9NMx2wkrzj5TxEBImVUptcyl/dkWXo4ETXqRM99x2ACavo7oqRC/RsAoqD2KewxLO7p1LDdZWx/4WAqiKt8W+Wd6NB3HP31jBQCWvYS7NUAxSru3t3/BOx3t6jKhCbMU85cF1VRPW49aqMGUF64Hy+g0XPHtKcUb6qvhq/vrqfpGelR5CTHEUdmJoZxeXLAAp3Ajqs4soBA8slKDCpJjUXFDuZfZiZ9iHSEyWRj7cdqPV/eCQxXW5Dv9ISVy6gRaxAzReRt9SIdRa3FoRy1EyIx0UWj+2BmCqvgDwpMToyGAB2LXTCzKlaAkREtRgqB+ciK9gI8Msu/5GqZlO90f37o/FHsz/gpvkZ/PtkwULbL/KgGSecPExuo4oKQBBfBGRCQima9IikjwTzdjsUfeyZJi92dM47dP5K+cpdt+nFkp62TUO3P9x7mNp1DVcBLMIs0O60XD7i7s/YBWSp4oQgMNgiBz710pxlXKBRzgm8S6Wy9uF8DTzvGAyqITiO+fInhTuUcjB/0IDCiCAHxQokP/3rxi2yCJgSXWPwFkf4B6WgAo9S8FfCBX2luHKP+zrX+F//fOr0ZPjHLqa/pkFp2PxNBxJaKImAerK9t1uV3tFxW5e4FOgpd24MQpbOFTjzTrIK0gWRhfsYm/nsScT8n2NvrKMJbf/9lmCyD7KRcvoWgl0UeJ2OnqZx45HVycrzb04cJApVi4QCnMx4kwQDfCieAAlU37edvdhOYKkBDJW7zjUZdFpGAL1bjGNYnU1uOjvVQvVe0VcNRPzO5Vl4D2cTIOh35n5YuEd4LCC8xB6bYHPQCOKIJTPEch4mG/qEupmO3Am5dce4mc2Dr9Pb9C4q5wyu5Pp9aPLka6nO7iBdJ9mr60wFoEJ6HxlAIx5J2npN2wPBsxvresF4dHYcBPmPs2J8d5MbKRezIcYscIA+p8hFdngdTqG1uoF/9pp3owdVbuXYTbpMx+92/l4XleFRk5NuPZNTqc8KomZknnJEHvffyvzypkBOBrK9sBdOIr34ne+e/3/UjvknwiAJXsPxfqPzlrPaCIPGEbjPiV6333xUJD8r4PY3flqxeedfbvxvqzfiO0f5xXACI0jIzxVnsuRkUeHWmaJe69zFxpGDl0ruIkq4Yx/yftQHtP49hXnSpXDt43ibxp8kHPy5hFHPGzK8FwZeYrTci8aOVbIsyw7TAuoJILVUpaXJX2sP/WyNQXXLSVAWg4x48vU6Lj3jOAYgwlImWqYIYfKwxnq+Q4OxJ4nzX0qVMDw6vIakdbqcbpEcCErTvfLrLfq6u85h9/5fPbQ4/L/2+SPP22O2358+j1vOxOMeLfcMkx79pYT/q9HfQDJctCYK/WgDERHzEQAhXTU+KxNPkHr4LF7jBUfGw3i1I/nNc2/x2bO7xMYsGEZeikc4w1lIghPD5XrpjofPMm3TpTvyfM5aXvwMcmchDTiSwFszyvhcTloTph1lJlNCKkSwcXOxcWaTfACrwadW+pXd7/sCIQbw7lPsz5VYv6syaYF4BjeOHQMjxMS/9zcwxweYJsOluHjZKiF4mH3QETBXFfofrqfHnFW8roDIh+b5eOFHHJwPADsnxNStgPXKk6uBr6bCBvRRjDgUGvpnMnA2kIJ6pYMtVlbm4EyXG5VyquqZ6GwOTEN+mX/lydMANK1ORBZhtowgjJj0pIvwWH4EARTgU8yRg+J6D18xIXIR2NJQKqRrF8JebMpVk5liAeU9+SbolgbIYehjYdjNoXp4D10nQrOR5CPbURuU1g+HE9K/3HoavvH8rZHVpPBdm5GyNDEsjtIo8KIDv94nIPHo7zOec5FI/S/aML7luSub/42eRG+4EKEQhZvPVvTLRZJW2hyKR/wHL1qNFsdepuJNd/H9d1YGf7/JsLOuBUhEDIzSwb63pM8vi4TiKtNIyU711IrRNw+EdoMsqVF9fXkSvGUmhzGtKcLGaTe10X2Dero3DI+ZbjBegx/AS/4SdLiIAmk2G7oJvkfAR0BzuYWgqnMOK5A0RRnNkdEMNVv0CoWdTmtRpTlikUs46yw7D/aV9BcA0Rk0NNUQLq7Vc2+RJBGKqGhYXZhwXoWcYc3xZfpLETkGm2cdYURc/jAGZvb6H9wqhpz8773Fwqb4GP2Kb9cTQ3IR/ZXn9RbOdqMUXs5aPTmGcCr+J6ADc5Cgp2gH2rSmusCTq/lPaZXQRG71DKOLauR7UkStvP/26Fe3JZ/hVc53mn5FQEDzUsHJGxS5FvBrAr0RNrjiRojrpwAu3M4TT15o/J9osW4CovHVo1oANo4/yI4BNR/vIkKcJUSDC1L7FIUDooUW4Zrg3Xmb05WIALqcSzuDH5nsp/TPyPiRfWkst5sSj8FwmNL2oseXUqwGbVTmXZhbtwGBgCFy0yvm8vqk7rq1g11Ahch59vHOxILDauO7ydBLPsi2deAvb3oXVUr2rPJU9rXI33W5EXbdcu/knDbXzBUAyJliKC9ZS+2U6mwEHQTl/SuIYgIHI+bazwNOwBqITGNnkcUGAGShzHnVl6tC2t6aQUbB+KDyTzr1cqQPVD5Vzpu5LSBvSYzURNSTOsqIqhn4YXYzl4RLbGjexKGaY+AtDGgddqdzcFSXc5BMykzcdxo5bcQglDaV4jb0GMNkil+pIM/mVfTxbO1gTBRwEoy0tYs0SPotTSIKXmgGdrSnvifXr6XXyxkJw/rMkAco87EI6VkTItUxP8ACYD2f0ASQADBBl5M/yoj5yKx6HecnXsDJtEpNTJc8mC6lJu/irTGOcvNysIoYfSV8DVW3iYTiJa44A0owFyRmcdVC5dVicYNKGlbNiKo4v5+8k704upYtyneNZdkK4CVtlHs/FTzxmkcomkukYWFhwenL6gA8u6UDvz+dlPQsvwIsCbvRj1Zb/0bquGRvl2WFtaS4KIzPfFpTGDYiOyTrIZ0BxMMu/QHMJFVpo84mFhss8skrQe+/1ySklaNnD3+faBwQofzyalIJZij1QkTyV2hgUhw38IBUMmkgaSaKkPzknaYGjLlv+UkodUAoy/MWEivPArn4jF+TSc829BUD5GttfVCGOOZwKIpu73wMBgXGLACJubq09Jdi7mVj85FRDgpOtkfs/slGAFMQ7jDgeIStu5vCU2nxv5eDLcWiFNsJ8I8kBEJALKU+SEIXMsu1DWSp5n7QoutkSCvClRNvbzqBBFXXhQ1ia44AVqCsBH9qqo1vOjYpgoRnCzk6VSMeKTkAFR80leHZlmjQVs8fmKMHA6otjfnrYGaGbjguSF+wNaxE9CgRpXxkgusZTwoBdE3Ghib4gSowRa3o2Kwx6kSE7/5Hz+y+tHlfwhnApooAqgouxTqivJKuOY1r+/LegBOwgtkoax11IR6KEn0mdvEAo2Ng6rRfpKlWX2KIs6xcd9js70uCR1JTN/xikUoVW4lltBd+XoVl4xHTykFyD0QciDFkz04MCtlJdqKI3GWTlbCgOy9GRi2kxa7KDwxN+FBnL5LqXiWtI5LOQl59GwI49wnh0KqJZOW6d00sZ45d+vI0eHaj0K4Sg9wth91yBcoH5Am407l6OcIRfI4Fyh4yx67izeRqUGPZ80pNATd6rF8d+HqMbL8u/6fP9Pr9xOG2GegVJatNI4OVN6Imkzyxi+G1ihylHH2U1SwTCye2deIYJMD35HJnvHzgYlMNjlE/JFkTTMh/SUam6kEsrozBQZwnBTBwYhvzJ9SYijFwncSgazt8nfSdMH51gO7My+zaZYBY7Hxk3fW4DmeQj4sVMFsQvGu79RSWt2Waqi077eK6ACRZD4BuGsgkA6OaEolqCBDC5K2cOb9HqV3FgnOJXfkiPwBMUYfQm2PV2YzJIbbmbMVJVS9XLONNqngSJgQ/CyUpJ9jEaT86V2/P1+OqE9Qop4ZX+DAIN3EF8hb3vfdLWjrcRKkt6Fx3UO9Kkun9llUB/nCEIVNlHuKvA5XuM1v3EePzjJzqv+O0RJPDVGaeg+bEEpwPMFaB9QpnjvKxW1GOMfiTZfTVEb6MoizGItHxtXoXIqiVnuXKXXGDBa6X1I4wDp1tbIa6/qloPF2ZEHB7znYYmMSG+KdgUAGxnCCo77QtKOmN4REC30jHngIiruoldycsDh9SA1OlQK11ijQVZkwbNDg6E8cl+EZ+i7UblCT/gAPHOubTkMHIFob7qw4xVng854q+dD/OMGBbp99HjaHTjHHnTrReG+nYc6FqIRQNP7nYvgNIVX1/f5Htkb40dQBj4sEgdNAmKZJNSDIXJQlZsYrfF2Oe3mbj5FM7Ec4jRCFxHRZO5kMMRlMozDa1xWqwHaZXA2C9WhU/8h2fJt2dOBDQNr2yFo1D2evN1Y4leVCb17Xay9VIkyjYnXerm6OEHhjTxXtkJtz5FjR8SuAgR3reW0laADnJGHoI7getb6oGkByfEKKvclllL2vlbNY+ypYQWwxpKSZ3fPrHY07GWo/q2QM3c/v3ztdJ5t6jWgYoHMyv0SPmd+KoVeFr8Bi/oC/MeDi1onXS3h3wFccbfYNHaVNqSdRihIDyPHH0YgMm4RPEgTL/WYC+f418fEzbcKP96N3PQk67C/HAoRKYQG739WkkaH/osMWsJqvuLOrkfkLBhNVR/jefKFLlTK7kwoHW36EGOoTWp+zElw35uVsrXDFfqNaI8AuNzblQ7eUsFW2AQqK0uL4OT+MTnAq+SkTguVbXckyogsVFeY4/FGjP8qTvXZje17KMuwdXRa27p0xTqRQueDh7nM9183uF7hgqbJ8UFR2Nmc4cL6ekPrYLBM0J/oo6x/FnOVGVd46+SpmXYMVg5EVyZciziyRXdVnSFJbO8f1P9xbpEdosKakZNcV8Zs9o9n9MEFazXyH7T8H1zQrlRbbvCofgUe4ahd3mVzXHVALTERLebiftCjVcLDobW1illEj6Gu1hF+HNOo0uOGIuCr1+hZhR6VpDdowfBumeTnAcu5bpP+5cBDxZM6IZ6MZfiQytMIjJJ5nmgdIM9a1LSv8YK61V6sFQMr1L4/rTOBuz6+RJO0ZW5GBqNYZ6T0Mq+ExpU0SzXzQxgraiQ2/MBwTr3FKpx07h4wkYC9NIEKXCUsN94g=
*/