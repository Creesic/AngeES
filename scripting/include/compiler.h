#ifndef ATG_ENGINE_SIM_COMPILER_H
#define ATG_ENGINE_SIM_COMPILER_H

#include "language_rules.h"

#include "engine_sim.h"
#include "piranha.h"

#include <vector>
#include <string>

namespace es_script {

    class Compiler {
    public:
        struct Output {
            Engine *engine = nullptr;
            Vehicle *vehicle = nullptr;
            Transmission *transmission = nullptr;
            Simulator::Parameters simulatorParameters;
            ApplicationSettings applicationSettings;

            std::vector<Function *> functions;
        };

    private:
        static Output *s_output;

    public:
        Compiler();
        ~Compiler();

        static Output *output();

        void initialize();
        bool compile(const piranha::IrPath &path);
        Output execute();
        void destroy();

        // Formatted compile errors from the most recent compile() call (empty on success).
        const std::vector<std::string> &getErrors() const { return m_errors; }

    private:
        void printError(const piranha::CompilationError *err, std::ofstream &file) const;
        std::string formatError(const piranha::CompilationError *err) const;

    private:
        LanguageRules m_rules;
        piranha::Compiler *m_compiler;
        piranha::NodeProgram m_program;
        std::vector<std::string> m_errors;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_COMPILER_H */