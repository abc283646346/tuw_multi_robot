/*
 * Copyright (c) 2017, <copyright holder> <email>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef BACKTRACKING_AVOID_RESOLUTION_H
#define BACKTRACKING_AVOID_RESOLUTION_H

#include <tuw_global_planner/srr_utils.h>
#include <tuw_global_planner/route_coordinator.h>
#include <tuw_global_planner/collision_resolution.h>

class BacktrackingAvoidResolution : public CollisionResolution
{
public:     
  BacktrackingAvoidResolution(uint32_t _timeoverlap);

  void resetSession(const RouteCoordinator *_route_querry, const PotentialCalculator *_pCalc, const uint32_t _robot_radius);
  std::vector<std::reference_wrapper<Vertex>> resolve(Vertex &_current, Vertex &_next, int32_t _collision);
private:	
  void trackBack(Vertex &_current, Vertex &_next, const int32_t _collision, const float _freePotential);
  void avoid(Vertex &_current, Vertex &_next, const int32_t _collision, const float _freePotential);
  void moveSegment(Vertex &_current, Vertex &_next, const int32_t _collision, const float _freePotential);
  void avoidStart(Vertex &_current, Vertex &_next, const int32_t _collision, const float _freePotential);
  void addCollision(const uint32_t robot);
  //void avoidEnd(std::shared_ptr< Segment > _current, std::shared_ptr< Segment > _next, float _newPot, int _robot_radius, std::vector<std::shared_ptr<Segment>> &retVal, int _collision);


//private:	std::vector<int> avoidedSegments_;


private:
  //bool isCrossing(const Vertex& _current, const Vertex& _next) const;
  const RouteCoordinator *route_querry_;
  const PotentialCalculator *pCalc_;
  uint32_t timeoverlap_;
  uint32_t robotDiameter_;
  //unique_ptr to keep references of Vertex (Heap), because the list is updated while runtime
  std::vector<std::vector<std::unique_ptr<Vertex>>> generatedSubgraphs_;        
  std::vector<std::reference_wrapper<Vertex>> foundSolutions_;
  std::vector<int> encounteredCollisions_;
  uint32_t resolutionAttemp_ = 0;
};

#endif // HEURISTIC_H
