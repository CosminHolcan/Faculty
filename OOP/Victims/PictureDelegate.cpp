#include "PictureDelegate.h"
#include <QPixmap>
#include <QPainter>

PictureDelegate::PictureDelegate(QWidget* parent) : QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QString photo = index.model()->data(index, Qt::EditRole).toString();
	if (index.column() != 3)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	if (photo.contains("TheKing"))
	{
		QPixmap pixMap("TheKing.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("the_king_of_pop.jpg"))
	{
		QPixmap pixMap("the_king_of_pop.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("ElPatron.jpg"))
	{
		QPixmap pixMap("ElPatron.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("robochild.jpg"))
	{
		QPixmap pixMap("robochild.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (photo.contains("pabloPicasso.jpg"))
	{
		QPixmap pixMap("pabloPicasso.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else
	{
		QPixmap pixMap("unknown.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == 3)
	{
		return QSize(140, 200);
	}
	return QStyledItemDelegate::sizeHint(option, index);
}
