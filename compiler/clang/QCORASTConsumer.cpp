#include "QCORASTConsumer.hpp"
#include "LambdaVisitor.hpp"

using namespace clang;

namespace qcor {
namespace compiler {
QCORASTConsumer::QCORASTConsumer(CompilerInstance &c, Rewriter& rw)
    : ci(c), fuzzyParser(std::make_shared<FuzzyParsingExternalSemaSource>(
                 c.getASTContext())), rewriter(rw) {}

bool QCORASTConsumer::HandleTopLevelDecl(DeclGroupRef DR) {

  LambdaVisitor visitor(ci, rewriter);
  ci.getSema().addExternalSource(fuzzyParser.get());
  for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
    visitor.TraverseDecl(*b);
  }

  return true;
}
} // namespace compiler
} // namespace qcor