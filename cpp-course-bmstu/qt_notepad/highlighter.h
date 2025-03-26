#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>

struct HighlightingRule {
    QRegularExpression pattern;
    QTextCharFormat format;
};

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT
public:
    Highlighter(const QString&,
                QTextDocument *parent=nullptr,
                const QString &style_filename=":/highlighter.xml");
    bool isSupported();

protected:
    void highlightBlock(const QString &text) override;

private:
    QVector<HighlightingRule> rules;
    bool supported;
    QTextCharFormat multiLineCommentFormat;
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
};

#endif

