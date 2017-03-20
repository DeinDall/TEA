#include "codestatement.h"

#include "lang/core/expression/abstractexpression.h"

#include "core/rom/romutil.h"

namespace tea {

CodeStatement::CodeStatement(const CodeTemplate* codeTemplate, QList<AbstractExpression*> parameters, QObject* parent)
	: AbstractStatement(parent), mCodeTemplate(codeTemplate), mParameters(parameters) {}

PrintHint CodeStatement::printHint() const {
	return mCodeTemplate->printHint();
}

QList<Token> CodeStatement::toTokens() const {
	QList<Token> result;

	result.append({ Token::Identifier, QVariant(mCodeTemplate->name()) });

	for (AbstractExpression* exp : mParameters)
		result.append(exp->toTokens());

	return result;
}

void CodeStatement::compute(CodeAssembler* assembler) const {
	auto it = mParameters.begin();
	auto componentIt = mCodeTemplate->parameters().cbegin();

	QByteArray data = mCodeTemplate->fixedData();

	while (componentIt != mCodeTemplate->parameters().cend()) {
		if (it == mParameters.end())
			return;

		uint size = (*componentIt).bitSize;
		uint offset = (*componentIt).bitOffset;

		if ((*it)->canCompute(assembler)) {
			(*componentIt).fillBits((*it)->compute(assembler), data);
			(*it)->deleteLater();
		} else
			assembler->markExpressionUsage(assembler->currentOffset()*8 + offset, size, (*it));

		++it;
		++componentIt;
	}

	assembler->writeData(data);
}

const CodeTemplate* CodeStatement::codeTemplate() const {
	return mCodeTemplate;
}

} // namespace tea
