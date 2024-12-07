#pragma once

enum class LAYER {
	DEFAULT,
	BACKGROUND,
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE,
	END
};

enum class PEN_TYPE {
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE {
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, BLACK, END
};

enum class EVENT_TYPE {
	DELETE_OBJECT,
	DELETE_UI,
	SCENE_CHANGE,
	END,
};

enum class RENDER_TYPE {
	BitBlt, TransparentBlt, StretchBlt
};
