#include "VictimsTableModel.h"

int VictimsTableModel::rowCount(const QModelIndex& parent) const
{
	return this->service.serviceGetVictimsMylist().size();
}

int VictimsTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant VictimsTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Victim victim = this->service.serviceGetVictimsMylist()[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(victim.getName());
		case 1:
			return QString::fromStdString(victim.getPlaceOfOrigin());
		case 2:
			return QString::fromStdString(to_string(victim.getAge()));
		case 3:
			return QString::fromStdString(victim.getPhotograph());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant VictimsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString("Name");
			case 1:
				return QString("Place");
			case 2:
				return QString("Age");
			case 3:
				return QString("Photograph");
			default:
				break;
			}
		}
	}
	return QVariant();
}

Qt::ItemFlags VictimsTableModel::flags(const QModelIndex& index) const
{
	/*
	int column = index.column();
	if (column == 0 || column == 1 || column == 2)
		return Qt::ItemFlags{};
		*/
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
