#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType) {
	type = texType;

	int widthImg, heightImg, numColCh; //image width & height and amount of colour channels
	//flips image to the correct side
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0); //loc, width, height, num of colour channels and desired channels

	GLuint texture;
	glGenTextures(1, &ID); //num. of textures & reference variable
	glActiveTexture(GL_TEXTURE0 + slot); //choosing the slot you want to use for the texture
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID); //type of texture and the var

	/*when scaled up or down we need to choose between GL_NEAREST and GL_LINEAR,
	GL_NEAREST keeps all the pixels as is and can appear pixelated when scaled up to high (more for pixel art)
	GL_LINEAR which makes new pixels according to pixels nearby (may make image blurier
	*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //type of texture, setting, what we want to change inside setting
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//textures can be repeated a few ways, GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE and GL_CLAMP_TO_BORDER. you can mix and match since they only aplly on one axis. s = x, t = y, z = r

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	/*GL_CLAMP_TO_BORDER:
		float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f,};
		glTexParamterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
	*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes); //Texture type, ~, type of col channels, width, height, ~, color channels our image has, datatype of pixels, image info
	glGenerateMipmap(GL_TEXTURE_2D); //smaller resolution versions

	stbi_image_free(bytes); //delete data
	glBindTexture(GL_TEXTURE_2D, 0); //unbind texture


}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint tex0uni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(tex0uni, unit);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}