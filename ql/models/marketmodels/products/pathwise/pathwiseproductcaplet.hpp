/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Mark Joshi

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#ifndef quantlib_market_model_pathwise_caplet_hpp
#define quantlib_market_model_pathwise_caplet_hpp

#include <ql/types.hpp>
#include <vector>
#include <memory>
#include <ql/models/marketmodels/pathwisemultiproduct.hpp>
#include <ql/models/marketmodels/evolutiondescription.hpp>

namespace QuantLib {

    class EvolutionDescription;
    class CurveState;

    //! market-model pathwise caplet
    /*! implementation of path wise methodology for caplets

    */

    class MarketModelPathwiseMultiCaplet : public MarketModelPathwiseMultiProduct
    {
     public:
        struct CashFlow {
            Size timeIndex;
            std::vector<Real > amount;
        };

       MarketModelPathwiseMultiCaplet(
                          const std::vector<Time>& rateTimes,
                          const std::vector<Real>& accruals,
                          const std::vector<Time>& paymentTimes,
                          const std::vector<Rate>& strikes);

        virtual ~MarketModelPathwiseMultiCaplet() {}

        virtual std::vector<Size> suggestedNumeraires() const;
        virtual const EvolutionDescription& evolution() const;
        virtual std::vector<Time> possibleCashFlowTimes() const;
        virtual Size numberOfProducts() const;
        virtual Size maxNumberOfCashFlowsPerProductPerStep() const;
        //! during simulation put product at start of path
        virtual void reset();

             //! return value indicates whether path is finished, TRUE means done
  
          virtual bool nextTimeStep(
            const CurveState& currentState,
            std::vector<Size>& numberCashFlowsThisStep,
            std::vector<std::vector<MarketModelPathwiseMultiProduct::CashFlow> >& cashFlowsGenerated) ;
    
        //! returns a newly-allocated copy of itself
        virtual std::auto_ptr<MarketModelPathwiseMultiProduct> clone() const;

    private:
        std::vector<Real> rateTimes_;
        std::vector<Real> accruals_;
        std::vector<Time> paymentTimes_;
        std::vector<Rate> strikes_;
        Size numberRates_;
        // things that vary in a path
        Size currentIndex_;
        
        EvolutionDescription evolution_;
    };


}


#endif