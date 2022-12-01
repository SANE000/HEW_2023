


#include "preview_collision.h"
#include "block.h"
#include "blockpreview.h"
#include "collision.h"
#include "player.h"

bool PreviewCollisionCheck()
{
	PREVIEW_BLOCK* pb = GetPreviewBlock();
	BLOCK* b = GetBlock();
	PLAYER* player = GetPlayer();

	bool check = false;

	for (int p = 0; p < PREVIEW_BLOCK_MAX; p++)
	{
		if (pb[p].use == false)
		{
			continue;
		}

		for (int i = 0; i < BLOCK_MAX; i++)
		{
			if (b[i].use == false)
			{
				continue;
			}
			//�v���C���[����480�͈͓̔��̂ݔ��肷��
			else if (b[i].pos.x <= player->pos.x - 240.0f || b[i].pos.x >= player->pos.x + 240.0f)
			{
				continue;
			}

			//�v���r���[�u���b�N���u���b�N�Əd�Ȃ�Ƃ���ɂ�����true
			if (pb[p].pos.x > b[i].pos.x - SIZE / 2 && pb[p].pos.x < b[i].pos.x + SIZE / 2
				&& pb[p].pos.y > b[i].pos.y - SIZE / 2 && pb[p].pos.y < b[i].pos.y + SIZE / 2)
			{
				check = true;
				break;
			}

		}

		if (check == true)
		{
			break;
		}
	}

	return check;
}
