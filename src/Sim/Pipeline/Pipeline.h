// 
// Copyright (c) 2005-2008 Kenichi Watanabe.
// Copyright (c) 2005-2008 Yasuhiro Watari.
// Copyright (c) 2005-2008 Hironori Ichibayashi.
// Copyright (c) 2008-2009 Kazuo Horio.
// Copyright (c) 2009-2015 Naruki Kurata.
// Copyright (c) 2005-2015 Ryota Shioya.
// Copyright (c) 2005-2015 Masahiro Goshima.
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 
// 3. This notice may not be removed or altered from any source
// distribution.
// 
// 


#ifndef SIM_PIPELINE_PIPELINE_H
#define SIM_PIPELINE_PIPELINE_H

#include "Sim/Pipeline/PipelineLatch.h"
#include "Sim/Foundation/TimeWheel/TimeWheelBase.h"

namespace Onikiri
{
    class PipelineNodeIF;

    class Pipeline : public TimeWheelBase 
    {
    public:
        Pipeline();
        virtual ~Pipeline();

        virtual void EnterPipeline( OpIterator op, int time, PipelineNodeIF* lowerNode );
        virtual void ExitPipeline( OpIterator op, PipelineNodeIF* lowerNode );
        virtual void AddUpperPipelineNode( PipelineNodeIF* node );
        virtual int  GetOpCount();
        
        virtual void Retire( OpIterator op );
        virtual void Flush( OpIterator op );

        void EnableDumpStall( bool enable );

        // --- TimeWheelBase
        virtual void BeginStall();
        virtual void EndStall();

    protected:
        bool m_enableDumpStall;

        std::vector<PipelineNodeIF*> m_upperPipelineNodes;
        
        typedef pool_list<OpIterator> List;
        List m_opList;
    };

}; // namespace Onikiri

#endif // SIM_PIPELINE_PIPELINE_H

