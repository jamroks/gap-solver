/*
This file is part of gap_solver.

gap_solver is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

gap_solver is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with gap_solver. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONSTANT_H

#define CONSTANT_H
#define UNEVALUATED 	2  	// valeur de travail; ne doit pas apparaître en début ou fin d'itération 
#define NO_JOB		1	// pas de tâche disponible pour le calcul du voisinage 
#define NO_AGT 		2	// pas de d'agent disponible pour le calcul du voisinage 

#define MAX_JOB		500
#define FALSE		0
#define TRUE		1
#define NO_VALUE	30000

#define INPUT_MAX_STRING_PARAMETER_VALUES	20

#define INPUT_TEMPERATURE_SCHEDULE_EQUAL		"equ"
#define INPUT_TEMPERATURE_SCHEDULE_LINEAR_1	"li1"
#define INPUT_TEMPERATURE_SCHEDULE_LINEAR_2	"li2"
#define INPUT_TEMPERATURE_SCHEDULE_LINEAR_3	"li3"
#define INPUT_TEMPERATURE_SCHEDULE_LOGARITHMIC_1	"lo1"
#define INPUT_TEMPERATURE_SCHEDULE_LOGARITHMIC_2	"lo2"
#define INPUT_TEMPERATURE_SCHEDULE_LOGARITHMIC_3	"lo3"
#define INPUT_TEMPERATURE_SCHEDULE_EXPONENTIAL_1	"ex1"
#define INPUT_TEMPERATURE_SCHEDULE_EXPONENTIAL_2	"ex2"
#define INPUT_TEMPERATURE_SCHEDULE_EXPONENTIAL_3	"ex3"

#define INPUT_STEP_SCHEDULE_EQUAL		"equ"
#define INPUT_STEP_SCHEDULE_ASCENDING_1	"as1"
#define INPUT_STEP_SCHEDULE_ASCENDING_2	"as2"
#define INPUT_STEP_SCHEDULE_ASCENDING_3	"as3"
#define INPUT_STEP_SCHEDULE_DESCENDING_1	"de1"
#define INPUT_STEP_SCHEDULE_DESCENDING_2	"de2"
#define INPUT_STEP_SCHEDULE_DESCENDING_3	"de3"
#define INPUT_STEP_SCHEDULE_NORMAL_1	"no1"
#define INPUT_STEP_SCHEDULE_NORMAL_2	"no2"
#define INPUT_STEP_SCHEDULE_NORMAL_3	"no3"

#define INPUT_MAXIMIZATION	"max"
#define INPUT_MINIMIZATION	"min"

#define INPUT_NEIGHBOURHOOD_EXPLORATION_DETERMINIST	"det"
#define INPUT_NEIGHBOURHOOD_EXPLORATION_STOCHASTIC	"sto"

#endif
