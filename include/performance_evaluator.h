// Copyright(c) 2016 - 2017 Costantino Grana, Federico Bolelli, Lorenzo Baraldi and Roberto Vezzani
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// *Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and / or other materials provided with the distribution.
//
// * Neither the name of YACCLAB nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once
#include "opencv2/opencv.hpp"

class PerformanceEvaluator {
    struct Elapsed {
        double last;
        double total;

        Elapsed() : last(0), total(0) {}
    };

public:
    PerformanceEvaluator()
    {
        tick_frequency_ = cv::getTickFrequency();
    }
    void start()
    {
        counter_.last = (double)cv::getTickCount();
    }
    double stop()
    {
        double t = cv::getTickCount() - counter_.last;
        counter_.last = t;
        counter_.total += t;
        return counter_.last*1000. / tick_frequency_;
    }
    void reset()
    {
        counter_.total = 0;
    }
    double last()
    {
        return counter_.last*1000. / tick_frequency_;
    }
    double total()
    {
        return counter_.total*1000. / tick_frequency_;
    }

    void start(const std::string& s)
    {
        counters_[s].last = (double)cv::getTickCount();
    }
    double stop(const std::string& s)
    {
        Elapsed& e = counters_[s];
        double t = cv::getTickCount() - e.last;
        e.last = t;
        e.total += t;
        return e.last*1000. / tick_frequency_;
    }
    void reset(const std::string& s)
    {
        counters_[s].total = 0;
    }
    double last(const std::string& s)
    {
        return counters_[s].last*1000. / tick_frequency_;
    }
    double total(const std::string& s)
    {
        return counters_[s].total*1000. / tick_frequency_;
    }

private:
    double tick_frequency_;
    Elapsed counter_;
    std::map<std::string, Elapsed> counters_;
};