#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include "xmmintrin.h"
#include "pmmintrin.h"

void ForwardVTI(float **vp, float **u0, float **u1, float **u2)
{
  const int x_M, x_m, y_M, y_m,  p_rec_M, p_rec_m, p_src_M, p_src_m, time_M, time_m, nthreads, nthreads_nonaffine;
  float **epsilon, **delta, **damp, **src_coords, **src;
  const float dt, o_x, o_y;
  float r0 = 1.0F/(dt*dt);
  float r1 = 1.0F/dt;
  int time = 10;
  {
    for (int x = x_m; x <= x_M; x += 1)
    {
      for (int y = y_m; y <= y_M; y += 1)
      {
        float r14 = -6.24999986e-3F*u0[x + 4][y + 4];
        float r13 = 2.0F*epsilon[x + 4][y + 4];
        float r12 = 1.25e-1F*u0[x + 4][y + 2] - u0[x + 4][y + 3] + u0[x + 4][y + 5] - 1.25e-1F*u0[x + 4][y + 6];
        float r11 = 1.25e-1F*u0[x + 2][y + 4] - u0[x + 3][y + 4] + u0[x + 5][y + 4] - 1.25e-1F*u0[x + 6][y + 4];
        float r10 = 1.0F/(vp[x + 4][y + 4]*vp[x + 4][y + 4]);
        float r9 = 6.25000009e-3F*u0[x + 4][y + 2] - 5.0e-2F*u0[x + 4][y + 3] + 5.0e-2F*u0[x + 4][y + 5] - 6.25000009e-3F*u0[x + 4][y + 6];
        float r8 = 6.25000009e-3F*u0[x + 2][y + 4] - 5.0e-2F*u0[x + 3][y + 4] + 5.0e-2F*u0[x + 5][y + 4] - 6.25000009e-3F*u0[x + 6][y + 4];
        float r7 = 4.16666673e-3F*u0[x + 4][y + 2] - 3.33333338e-2F*u0[x + 4][y + 3] + 3.33333338e-2F*u0[x + 4][y + 5] - 4.16666673e-3F*u0[x + 4][y + 6];
        float r6 = (2.46913615111777e-6F*(r11*r11)*(r12*r12)*(delta[x + 4][y + 4] - epsilon[x + 4][y + 4]))/(r7*r7*r7*r7 + 1.97530864e-1F*(r8*r8)*(r9*r9)*(r13 + 2.0F) + 1.97530864e-1F*(r8*r8*r8*r8)*(2*epsilon[x + 4][y + 4] + 1.0F) + 1.19209e-7F);
        u2[x + 4][y + 4] = (r1*damp[x + 1][y + 1]*u0[x + 4][y + 4] + r10*(-r0*(-2.0F*u0[x + 4][y + 4]) - r0*u1[x + 4][y + 4]) + (r6 + 1.0F)*(r14 - 2.08333329e-4F*(u0[x + 4][y + 2] + u0[x + 4][y + 6]) + 3.33333326e-3F*(u0[x + 4][y + 3] + u0[x + 4][y + 5])) + (r13 + r6 + 1.0F)*(r14 - 2.08333329e-4F*(u0[x + 2][y + 4] + u0[x + 6][y + 4]) + 3.33333326e-3F*(u0[x + 3][y + 4] + u0[x + 5][y + 4])))/(r0*r10 + r1*damp[x + 1][y + 1]);
      }
    }
  }
  /* End section0 */

  /* Begin section1 */
  {
    int chunk_size = (int)(fmax(1, (1.0F/3.0F)*(p_src_M - p_src_m + 1)/nthreads_nonaffine));
    for (int p_src = p_src_m; p_src <= p_src_M; p_src += 1)
    {
      float posx = -o_x + src_coords[p_src][0];
      float posy = -o_y + src_coords[p_src][1];
      int ii_src_0 = (int)(floor(5.0e-2F*posx));
      int ii_src_1 = (int)(floor(5.0e-2F*posy));
      int ii_src_2 = 1 + (int)(floor(5.0e-2F*posy));
      int ii_src_3 = 1 + (int)(floor(5.0e-2F*posx));
      float px = (float)(posx - 2.0e+1F*(int)(floor(5.0e-2F*posx)));
      float py = (float)(posy - 2.0e+1F*(int)(floor(5.0e-2F*posy)));
      if (ii_src_0 >= x_m - 1 && ii_src_1 >= y_m - 1 && ii_src_0 <= x_M + 1 && ii_src_1 <= y_M + 1)
      {
        float r2 = (dt*dt)*(vp[ii_src_0 + 4][ii_src_1 + 4]*vp[ii_src_0 + 4][ii_src_1 + 4])*(2.5e-3F*px*py - 5.0e-2F*px - 5.0e-2F*py + 1)*src[time][p_src];
        u2[ii_src_0 + 4][ii_src_1 + 4] += r2;
      }
      if (ii_src_0 >= x_m - 1 && ii_src_2 >= y_m - 1 && ii_src_0 <= x_M + 1 && ii_src_2 <= y_M + 1)
      {
        float r3 = (dt*dt)*(vp[ii_src_0 + 4][ii_src_2 + 4]*vp[ii_src_0 + 4][ii_src_2 + 4])*(-2.5e-3F*px*py + 5.0e-2F*py)*src[time][p_src];
        u2[ii_src_0 + 4][ii_src_2 + 4] += r3;
      }
      if (ii_src_1 >= y_m - 1 && ii_src_3 >= x_m - 1 && ii_src_1 <= y_M + 1 && ii_src_3 <= x_M + 1)
      {
        float r4 = (dt*dt)*(vp[ii_src_3 + 4][ii_src_1 + 4]*vp[ii_src_3 + 4][ii_src_1 + 4])*(-2.5e-3F*px*py + 5.0e-2F*px)*src[time][p_src];
        u2[ii_src_3 + 4][ii_src_1 + 4] += r4;
      }
      if (ii_src_2 >= y_m - 1 && ii_src_3 >= x_m - 1 && ii_src_2 <= y_M + 1 && ii_src_3 <= x_M + 1)
      {
        float r5 = 2.5e-3F*px*py*(dt*dt)*(vp[ii_src_3 + 4][ii_src_2 + 4]*vp[ii_src_3 + 4][ii_src_2 + 4])*src[time][p_src];
        u2[ii_src_3 + 4][ii_src_2 + 4] += r5;
      }
    }
  }
};
