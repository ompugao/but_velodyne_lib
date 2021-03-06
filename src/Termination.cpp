/*
 * Copyright (C) Brno University of Technology (BUT)
 *
 * This file is part of software developed by Robo@FIT group.
 *
 * Author: Martin Velas (ivelas@fit.vutbr.cz)
 * Supervised by: Michal Spanel & Adam Herout ({spanel|herout}@fit.vutbr.cz)
 * Date: 22/05/2015
 *
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cmath>

#include <but_velodyne_odom/Termination.h>

namespace but_velodyne_odom
{

Termination::Termination(int min_iterations, int max_iterations, float max_time_spent,
            float min_err_deviation, float min_error) :
              err_deviation(min_iterations), min_error(min_error),
              max_time_spent(max_time_spent), max_iterations(max_iterations),
              iterations(0), min_err_deviation(min_err_deviation) {
  stopwatch.start();
  last_error = INFINITY;
}

void Termination::addNewError(float new_error) {
  last_error = new_error;
  err_deviation.add(new_error);
  iterations++;
}

bool Termination::operator()() {
  if(iterations >= max_iterations) {
    return true;
  }
  if(stopwatch.elapsed() > max_time_spent) {
    return true;
  }
  if(!err_deviation.isSignificant(min_err_deviation)) {
    return true;
  }
  if(last_error < min_error) {
    return true;
  }
  return false;
}

} /* namespace but_velodyne_odom */
