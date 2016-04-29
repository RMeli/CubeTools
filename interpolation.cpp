/*
 Copyright (C) 2016 Rocco Meli (rocco.meli@epfl.ch)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cmath>
#include <iostream>

#include <fftw3.h>

#include "interpolation.h"

std::vector<std::array<double,2>> fourier_interpolation(std::vector<std::array<double,2>> const& in, uint FN)
{
    uint N(in.size());

    if( FN < N)
    {
        std::cerr << "ERROR: Insufficient nodes for Fourier interpolation." << std::endl;
        std::cerr << "       FN >= N is required." << std::endl;

        std::exit(-1);
    }
    else if( FN == N)
    {
        std::cerr << "WARNING: No new nodes for Fourier interpolation." << std::endl;
        std::cerr << "         Original data returned, without interpolation." << std::endl;

        return in;
    }

    // Allocate memory for FFT input and output (complex vectors)
    fftw_complex* fft_in;
    fftw_complex* fft_out;
    fft_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fft_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    // Create FFTW forward plan
    fftw_plan pf = fftw_plan_dft_1d(N, fft_in, fft_out, FFTW_FORWARD, FFTW_ESTIMATE);

    for(uint i(0); i < N; i++)
    {
        fft_in[i][0] = in[i][1];
        fft_in[i][1] = 0.0;
    }

    // Compute FFT
    fftw_execute(pf);

    // FFT normalization (FFTW compute unnormalized FFT)
    for(uint i(0); i < N; i++)
    {
        // Normalize real part
        fft_out[i][0] = fft_out[i][0] / N;
        // Normalize complex part
        fft_out[i][1] = fft_out[i][1] / N;
    }

    // Allocate memory for Fourier interpolation
    fftw_complex* fft_newin;
    fftw_complex* fft_newout;
    fft_newin = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FN);
    fft_newout = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FN);

    // Create FFTW backward plan
    fftw_plan pb = fftw_plan_dft_1d(FN, fft_newin, fft_newout, FFTW_BACKWARD, FFTW_ESTIMATE);

    for(uint i(0); i < FN; i++)
    {
        if( i < N / 2 - 1 )
        {
            fft_newin[i][0] = fft_out[i][0];
            fft_newin[i][1] = fft_out[i][1];
        }
        else if( i > FN - N / 2 - 1)
        {
            fft_newin[i][0] = fft_out[i - FN + N][0];
            fft_newin[i][1] = fft_out[i - FN + N][1];
        }
        else
        {
            fft_newin[i][0] = 0.;
            fft_newin[i][1] = 0.;
        }
    }

    if( N % 2 == 0)
    {
        fft_newin[ N / 2 + 1 ][0] = 0.5 * fft_out[ N / 2 + 1][0];
        fft_newin[ N / 2 + 1 ][1] = 0.5 * fft_out[ N / 2 + 1][1];

        fft_newin[ FN - N / 2 + 1][0] = fft_newin[ N / 2 + 1 ][0];
        fft_newin[ FN - N / 2 + 1][1] = -fft_newin[ N / 2 + 1 ][1];
    }
    else
    {
        fft_newin[ N / 2 + 1 ][0] = fft_out[ N / 2 + 1][0];
        fft_newin[ N / 2 + 1 ][1] = fft_out[ N / 2 + 1][1];
    }

    // Compute FFT
    fftw_execute(pb);

    // Origin
    double o(in[0][0]);

    // New step
    double dl( (in[1][0] - in[0][0]));

    // New vector storing new data points (interval and iterpolant)
    std::vector<std::array<double,2>> out(FN,std::array<double,2>{{0.0,0.0}});

    // Fill output vector
    for(uint i(0); i < FN; i++)
    {
        // Store position
        out[i][0] = dl * N / FN * i + o;

        // Compute and store value at given position
        out[i][1] = fft_newout[i][0];
    }

    // Destroy plans
    fftw_destroy_plan(pf);
    fftw_destroy_plan(pb);

    // Free memory
    fftw_free(fft_in);
    fftw_free(fft_out);
    fftw_free(fft_newin);
    fftw_free(fft_newout);

    return out;
}
